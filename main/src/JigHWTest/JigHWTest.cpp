#include "JigHWTest.h"
#include "SPIFFSChecksum.hpp"
#include <soc/efuse_reg.h>
#include <esp_efuse.h>
#include <ctime>
#include <driver/gpio.h>
#include "Devices/RTC.h"
#include "Devices/IMU/IMU.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

JigHWTest* JigHWTest::test = nullptr;

JigHWTest::JigHWTest(I2C& i2c) : i2c(i2c){
	test = this;

	tests.push_back({ JigHWTest::RTCTest, "RTC" });
	tests.push_back({ JigHWTest::Time, "Time" });
	tests.push_back({ JigHWTest::Gyro, "Gyro" });

	imu = new IMU(i2c);
	rtc = new RTC(i2c);
}

void JigHWTest::start(){
	uint8_t mac[6];
	esp_read_mac(mac, ESP_MAC_WIFI_STA);
	uint64_t uid = 0;
	for(int i = 0; i < 6; i++){
		uid |= mac[i] << 8 * i;
	}

	printf("\n");
	printf("TEST:begin:%llx\n", uid);

	gpio_set_direction(GPIO_NUM_13, GPIO_MODE_OUTPUT);
	gpio_set_level(GPIO_NUM_13, 0);

	// canvas->clear(TFT_BLACK);
	// canvas->setTextColor(TFT_GOLD);
	// canvas->setTextWrap(false, false);
	// canvas->setTextDatum(textdatum_t::middle_center);

	// canvas->setTextFont(0);
	// canvas->setTextSize(1);
	// canvas->setCursor(0, 6);

	// canvas->printCenter("CircuitPet Hardware Test");
	// canvas->setCursor(// canvas->width() / 2, 16);
	// canvas->println();
	// display->commit();

	bool pass = true;
	for(const Test& test: tests){
		currentTest = test.name;

		// canvas->setTextColor(TFT_WHITE);
		// canvas->printf("%s: ", test.name);
		// display->commit();

		printf("TEST:startTest:%s\n", currentTest);

		bool result = test.test();

		// canvas->setTextColor(result ? TFT_GREEN : TFT_RED);
		// canvas->printf("%s\n", result ? "PASSED" : "FAILED");
		// display->commit();

		printf("TEST:endTest:%s\n", result ? "pass" : "fail");

		if(!(pass &= result)){
			// break;
		}
	}

	if(!pass){
		printf("TEST:fail:%s\n", currentTest);
		bool v = 0;
		for(;;){
			gpio_set_level(GPIO_NUM_13, v);
			v = !v;
			printf("%d\n", v);
			vTaskDelay(500);
		}
		return;
	}

	printf("TEST:passall\n");
	gpio_set_level(GPIO_NUM_13, 1);

	// canvas->print("\n\n");
	// canvas->setTextColor(TFT_GREEN);
	// canvas->printCenter("All OK!");
	// display->commit();


	/*Sound s = {{ 350, 400, 200 },
			   { 800, 800, 500 },
			   { 1000, 1000, 500 },
			   { 1200, 1200, 500 }
	};*/
//	Audio.play(s);
}

bool JigHWTest::RTCTest(){
	return test->rtc->init();
}

bool JigHWTest::Time(){
	if(!test->rtc->init()){
		return false;
	}

	static constexpr size_t count = 1000;
	time_t lastTimestamp;

	for(int i = 0; i < count; i++){
		auto time = test->rtc->getTime();
		auto timestamp = mktime(&time);

		if(i == 0){
			lastTimestamp = timestamp;
			continue;
		}

		auto diff = abs(difftime(timestamp, lastTimestamp));
		if(diff > 10.0f){
			test->log("reading", i);
			test->log("diff", diff);
			return false;
		}

		lastTimestamp = timestamp;
	}

	return true;
}

bool JigHWTest::Gyro(){
	return test->imu->init();
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
	printf("%s:%s:%u\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, int32_t value){
	printf("%s:%s:%d\n", currentTest, property, value);
}

void JigHWTest::log(const char* property, const std::string& value){
	printf("%s:%s:%s\n", currentTest, property, value.c_str());
}
