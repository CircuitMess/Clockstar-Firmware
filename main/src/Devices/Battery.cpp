#include "Battery.h"
#include "../Pins.hpp"
#include "Util/Events.h"
#include <soc/efuse_reg.h>
#include <Util/stdafx.h>
#include <cmath>
#include <driver/gpio.h>

Battery::Battery() : Threaded("Battery", 1024, 4), adc((gpio_num_t) PIN_BATT, 0.05), hysteresis(HysteresisThresholds){
	gpio_config_t cfg_gpio = {};
	cfg_gpio.mode = GPIO_MODE_INPUT;
	cfg_gpio.pull_down_en = GPIO_PULLDOWN_ENABLE;
	cfg_gpio.pull_up_en = GPIO_PULLUP_DISABLE;
	cfg_gpio.pin_bit_mask = 1ULL << PIN_CHARGE;
	ESP_ERROR_CHECK(gpio_config(&cfg_gpio));

	quickSample();
	level = hysteresis.update(getPercentage());
	start();
}

Battery::~Battery(){
	stop();
}

void Battery::quickSample(){
	uint32_t sum = 0;
	for(int i = 0; i < MeasureCount; i++){
		sum += adc.sample();
	}
	voltage = mapReading(sum / MeasureCount);
}

bool Battery::isCharging() const{
	return gpio_get_level((gpio_num_t) PIN_CHARGE) == 1;
}

bool Battery::isCritical() const{
	return getLevel() == 0;
}

void Battery::loop(){
	vTaskDelay(MeasureInverval);

	// TODO: send evt on chrg
	if(isCharging()){
		if(!wasCharging){
			Events::post(Facility::Battery, Battery::Event{ .action = Event::Charging, .chargeStatus = true });
			batteryLowAlert = false;
		}
		wasCharging = true;
		return;
	}else if(wasCharging){
		Events::post(Facility::Battery, Battery::Event{ .action = Event::Charging, .chargeStatus = false });

		wasCharging = false;
		adc.resetEma();
		quickSample();
		hysteresis.reset(getPercentage());
		measureSum = 0;
		measureCount = 0;
	}

	measureSum += adc.sample();
	measureCount++;

	if(measureCount < MeasureCount) return;

	voltage = mapReading(measureSum / MeasureCount);
	measureSum = 0;
	measureCount = 0;
	level = hysteresis.update(getPercentage());

	if(isCritical() && !batteryLowAlert){
		batteryLowAlert = true;
		Events::post(Facility::Battery, Battery::Event{ .action = Event::BatteryLow });
	}else if(!isCritical() && batteryLowAlert){
		batteryLowAlert = false;
	}
}

uint16_t Battery::mapReading(uint16_t reading){
#define MAX_READ 3550
#define MIN_READ 3050
#define MAX_VOLT 4200
#define MIN_VOLT 3600
	return std::round(map((double) reading, MIN_READ, MAX_READ, MIN_VOLT, MAX_VOLT));
}

uint8_t Battery::getLevel() const{
	return level;
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