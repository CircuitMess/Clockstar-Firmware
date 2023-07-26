#include "JigHWTest.h"
#include "SPIFFSChecksum.hpp"
#include <Pins.hpp>
#include <soc/efuse_reg.h>
#include <esp_efuse.h>
#include <ctime>
#include <iostream>
#include <esp_mac.h>
#include "Util/Services.h"
#include <driver/adc.h>
#include <driver/gptimer.h>
#include <driver/ledc.h>
#include "Devices/Input.h"
#include "Util/Events.h"


JigHWTest* JigHWTest::test = nullptr;
Display* JigHWTest::display = nullptr;
LGFX_Device* JigHWTest::canvas = nullptr;
I2C* JigHWTest::i2c = nullptr;
RTC* JigHWTest::rtc = nullptr;


JigHWTest::JigHWTest(){
	gpio_config_t io_conf = {
			.pin_bit_mask = 1 << JIG_STATUS,
			.mode = GPIO_MODE_OUTPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&io_conf);
	gpio_set_level(statusLed, 1);

	display = new Display();
	canvas = &display->getLGFX();

	i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);
	rtc = new RTC(*i2c);

	test = this;

	tests.push_back({ JigHWTest::RTCTest, "RTC", [](){} });
	tests.push_back({ JigHWTest::Time1, "RTC kristal", [](){} });
	tests.push_back({ JigHWTest::Time2, "RTC kristal", [](){} });
	tests.push_back({ JigHWTest::IMUTest, "Ziroskop", [](){} });
	tests.push_back({ JigHWTest::SPIFFSTest, "SPIFFS", [](){} });
	tests.push_back({ JigHWTest::BatteryCalib, "Batt kalib.", [](){} });
	tests.push_back({ JigHWTest::BatteryCheck, "Batt provjera", [](){} });
	//TODO - crystal test
}

bool JigHWTest::checkJig(){
	char buf[7];
	int wp = 0;

	uint32_t start = millis();
	int c;
	while(millis() - start < CheckTimeout){
		vTaskDelay(1);
		c = getchar();
		if(c == EOF) continue;
		buf[wp] = (char) c;
		wp = (wp + 1) % 7;

		for(int i = 0; i < 7; i++){
			int match = 0;
			static const char* target = "JIGTEST";

			for(int j = 0; j < 7; j++){
				match += buf[(i + j) % 7] == target[j];
			}

			if(match == 7) return true;
		}
	}

	return false;
}


void JigHWTest::start(){
	uint64_t _chipmacid = 0LL;
	esp_efuse_mac_get_default((uint8_t*) (&_chipmacid));
	printf("\nTEST:begin:%llx\n", _chipmacid);

	canvas->clear(0);
	gpio_set_level((gpio_num_t) PIN_BL, 0);
	rgb();

	canvas->clear(TFT_BLACK);
	canvas->setTextColor(TFT_GOLD);
	canvas->setTextWrap(true, true);
	canvas->setTextDatum(textdatum_t::middle_center);

	canvas->setTextFont(0);
	canvas->setTextSize(1);
	canvas->setCursor(0, 6);

	canvas->print("Clockstar test");
	canvas->setCursor(canvas->width() / 2, 16);
	canvas->println();

	bool pass = true;
	for(const Test& test : tests){
		currentTest = test.name;

		canvas->setTextColor(TFT_WHITE);
		canvas->printf("%s: ", test.name);

		printf("TEST:startTest:%s\n", currentTest);

		bool result = test.test();

		canvas->setTextColor(result ? TFT_GREEN : TFT_RED);
		canvas->printf("%s\n", result ? "PASSED" : "FAILED");

		printf("TEST:endTest:%s\n", result ? "pass" : "fail");

		if(!(pass &= result)){
			if(test.onFail){
				test.onFail();
			}

			break;
		}
	}

	if(!pass){
		printf("TEST:fail:%s\n", currentTest);
		gpio_set_level(statusLed, 0);
		vTaskDelete(nullptr);
	}

	printf("TEST:passall\n");

//------------------------------------------------------


	canvas->print("\n\n");
	canvas->setTextColor(TFT_GREEN);
	canvas->print("All OK!");

	AudioVisualTest();

}

void JigHWTest::rgb(){
	static const char* names[] = { "RED", "GREEN", "BLUE" };
	static const uint16_t colors[] = { TFT_RED, TFT_GREEN, TFT_BLUE };
	for(int i = 0; i < 3; i++){
		canvas->clear(colors[i]);
		canvas->setCursor(20, 40);
		canvas->setTextFont(0);
		canvas->setTextSize(2);
		canvas->print(names[i]);
		vTaskDelay(350);
	}
}

void JigHWTest::log(const char* property, const char* value){
	printf("%s:%s:%s\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, float value){
	printf("%s:%s:%f\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, double value){
	printf("%s:%s:%lf\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, bool value){
	printf("%s:%s:%s\n", currentTest, property, value ? "TRUE" : "FALSE");
}

void JigHWTest::log(const char* property, uint32_t value){
	printf("%s:%s:%lu\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, int32_t value){
	printf("%s:%s:%ld\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, const std::string& value){
	printf("%s:%s:%s\n", currentTest, property, value.c_str());
}

bool JigHWTest::BatteryCalib(){
	if(Battery::getVoltOffset() != 0){
		test->log("calibrated", (uint32_t) Battery::getVoltOffset());
		canvas->print("fused. ");
		return true;
	}

	constexpr uint16_t numReadings = 50;
	constexpr uint16_t readDelay = 50;
	uint32_t reading = 0;

	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);

	for(int i = 0; i < numReadings; i++){
		reading += adc1_get_raw(ADC1_CHANNEL_0);
		vTaskDelay(readDelay / portTICK_PERIOD_MS);
	}
	reading /= numReadings;


	uint32_t mapped = Battery::mapRawReading(reading);

	int16_t offset = referenceVoltage - mapped;

	test->log("reading", reading);
	test->log("mapped", mapped);
	test->log("offset", (int32_t) offset);

	if(abs(offset) >= 1000){
		test->log("offset too big, read voltage: ", (uint32_t) mapped);
		return false;
	}

	uint16_t offsetLow = offset & 0b01111111;
	uint16_t offsetHigh = offset >> 7;

	return true; //TODO - remove early return, burn to efuse

	esp_efuse_write_field_blob((const esp_efuse_desc_t**) efuse_adc1_low, &offsetLow, 7);
	esp_efuse_write_field_blob((const esp_efuse_desc_t**) efuse_adc1_high, &offsetHigh, 9);
	esp_efuse_reset();

	return true;
}


bool JigHWTest::BatteryCheck(){
	adc1_config_width(ADC_WIDTH_BIT_12);
	adc1_config_channel_atten(ADC1_CHANNEL_0, ADC_ATTEN_DB_0);

	constexpr uint16_t numReadings = 50;
	constexpr uint16_t readDelay = 10;
	uint32_t reading = 0;

	for(int i = 0; i < numReadings; i++){
		reading += adc1_get_raw(ADC1_CHANNEL_0);
		vTaskDelay(readDelay / portTICK_PERIOD_MS);
	}
	reading /= numReadings;

	uint32_t voltage = Battery::mapRawReading(reading) + Battery::getVoltOffset();
	if(voltage < referenceVoltage - 100 || voltage > referenceVoltage + 100){
		test->log("raw", reading);
		test->log("mapped", (int32_t) Battery::mapRawReading(reading));
		test->log("offset", (int32_t) Battery::getVoltOffset());
		test->log("mapped+offset", voltage);
		return false;
	}

	return true;
}

bool JigHWTest::SPIFFSTest(){

	auto ret = esp_vfs_spiffs_register(&spiffsConfig);
	if(ret != ESP_OK){
		test->log("spiffs", false);
		return false;
	}

	for(const auto& f : SPIFFSChecksums){
		auto file = fopen(f.name, "rb");
		if(file == nullptr){
			test->log("missing", f.name);
			return false;
		}

		uint32_t sum = calcChecksum(file);
		fclose(file);

		if(sum != f.sum){
			test->log("file", f.name);
			test->log("expected", (uint32_t) f.sum);
			test->log("got", (uint32_t) sum);

			return false;
		}
	}

	return true;
}

uint32_t JigHWTest::calcChecksum(FILE* file){
	if(file == nullptr) return 0;

#define READ_SIZE 512

	uint32_t sum = 0;
	uint8_t b[READ_SIZE];
	size_t read = 0;
	while((read = fread(b, 1, READ_SIZE, file))){
		for(int i = 0; i < read; i++){
			sum += b[i];
		}
	}

	return sum;
}

void JigHWTest::AudioVisualTest(){
	ledc_timer_config_t ledc_timer = {
			.speed_mode       = LEDC_LOW_SPEED_MODE,
			.duty_resolution  = LEDC_TIMER_10_BIT,
			.timer_num        = LEDC_TIMER_0,
			.freq_hz          = 200,
			.clk_cfg          = LEDC_AUTO_CLK,
			.deconfigure      = false
	};
	ledc_timer_config(&ledc_timer);

	ledc_channel_config_t ledc_channel = {
			.gpio_num       = PIN_BUZZ,
			.speed_mode     = LEDC_LOW_SPEED_MODE,
			.channel        = LEDC_CHANNEL_0,
			.intr_type      = LEDC_INTR_DISABLE,
			.timer_sel      = LEDC_TIMER_0,

			.duty           = 0,
			.hpoint         = 0,
			.flags = { .output_invert = 1 }
	};
	ledc_channel_config(&ledc_channel);

	new Input;
	EventQueue queue(1);
	Events::listen(Facility::Input, &queue);
	bool mute = false;

	for(;;){
		Event evt;
		if(queue.get(evt, 0)){
			auto data = (Input::Data*) evt.data;
			if(data->action == Input::Data::Press && data->btn == Input::Alt){
				mute = true;
			}
			free(evt.data);
		}

		if(!mute){
			ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, (1 << (10 - 1)) - 1);
			ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
		}
		gpio_set_level(statusLed, 1);
		vTaskDelay(500);

		if(!mute){
			ledc_set_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0, 0);
			ledc_update_duty(LEDC_LOW_SPEED_MODE, LEDC_CHANNEL_0);
		}
		gpio_set_level(statusLed, 0);
		vTaskDelay(500);
	}
}

bool JigHWTest::RTCTest(){
	auto ret = i2c->write(0x51, { 0, 0, 0 }, 10);
	if(ret == ESP_OK){
		test->log("begin", true);
	}else{
		test->log("begin", false);
		return false;
	}

	return rtc->init();
}

bool JigHWTest::Time1(){
	auto t = rtc->getTime();
	auto unixt = mktime(&t);

	vTaskDelay(2000 / portTICK_PERIOD_MS);

	auto t2 = rtc->getTime();
	auto unixt2 = mktime(&t2);
	auto diff = std::difftime(unixt2, unixt);

	if(diff != 1 && diff != 2){
		test->log("time passage (expected 1s or 2s)", (uint32_t) diff);
		return false;
	}

	return true;
}

bool JigHWTest::Time2(){
	static constexpr size_t count = 1000;

	time_t lastTime = 0;

	for(uint32_t i = 0; i < count; i++){

		auto t = rtc->getTime();
		auto unixt = mktime(&t);

		if(i == 0){
			lastTime = unixt;
			continue;
		}
		vTaskDelay(1);

		auto diff = abs(difftime(unixt, lastTime));
		if(diff > 1){
			test->log("reading", i);
			test->log("diff", diff);
			JigHWTest::canvas->printf("diff: %.2f", diff);
			return false;
		}

		lastTime = unixt;
	}
	return true;
}

bool JigHWTest::IMUTest(){
	uint8_t data;
	auto ret = i2c->readReg(0x6A, 0x0FU, &data, 1, 10);
	return ret == ESP_OK && data == 0x6AU;
}
