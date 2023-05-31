#include "Battery.h"
#include "../Pins.hpp"
#include <soc/efuse_reg.h>
#include <Util/stdafx.h>
#include <cmath>
#include <driver/gpio.h>

Battery::Battery() : Threaded("Battery", 4 * 1024, 4), adc((gpio_num_t) PIN_BATT, 0.05){
	gpio_config_t cfg_gpio = {};
	cfg_gpio.mode = GPIO_MODE_INPUT;
	cfg_gpio.pull_down_en = GPIO_PULLDOWN_ENABLE;
	cfg_gpio.pull_up_en = GPIO_PULLUP_DISABLE;
	cfg_gpio.pin_bit_mask = 1ULL << PIN_CHARGE;
	ESP_ERROR_CHECK(gpio_config(&cfg_gpio));

	uint32_t sum = 0;
	for(int i = 0; i < MeasureCount; i++){
		sum += adc.sample();
	}
	voltage = mapReading(sum/MeasureCount);

	start();
}

Battery::~Battery(){
	stop();
}

bool Battery::isCharging() const{
	return gpio_get_level((gpio_num_t) PIN_CHARGE) == 1;
}

void Battery::loop(){
	vTaskDelay(MeasureInverval);

	measureSum += adc.sample();
	measureCount++;

	if(measureCount < MeasureCount) return;

	voltage = mapReading(measureSum / MeasureCount);
	measureSum = 0;
	measureCount = 0;
}

uint16_t Battery::mapReading(uint16_t reading){
#define MAX_READ 3550
#define MIN_READ 3050
#define MAX_VOLT 4200
#define MIN_VOLT 3600
	return std::round(map((double) reading, MIN_READ, MAX_READ, MIN_VOLT, MAX_VOLT));
}

uint8_t Battery::getLevel() const{
	uint8_t percentage = getPercentage();

	if(percentage > 80){
		return 5;
	}else if(percentage > 60){
		return 4;
	}else if(percentage > 40){
		return 3;
	}else if(percentage > 20){
		return 2;
	}else if(percentage >= 5){
		return 1;
	}else if(percentage < 5){
		return 0;
	}

	return 0;
}

uint8_t Battery::getPercentage() const{
	int16_t perc = map((int16_t) getVoltage(), MIN_VOLT, MAX_VOLT, 0, 100);
	return std::clamp(perc, (int16_t) 0, (int16_t) 100);
}

uint16_t Battery::getVoltage() const{
	return voltage + getVoltOffset();
}

int16_t Battery::getVoltOffset(){
	return 0;
	uint32_t upper = REG_GET_FIELD(EFUSE_BLK3_RDATA3_REG, EFUSE_RD_ADC1_TP_HIGH);
	uint32_t lower = REG_GET_FIELD(EFUSE_BLK3_RDATA3_REG, EFUSE_RD_ADC1_TP_LOW);
	return (upper << 7) | lower;
}