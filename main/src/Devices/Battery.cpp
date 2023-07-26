#include "Battery.h"
#include "../Pins.hpp"
#include "Util/Events.h"
#include <soc/efuse_reg.h>
#include <Util/stdafx.h>
#include <cmath>
#include <driver/gpio.h>

#define MAX_READ 3550 // 4.2V
#define MIN_READ 3050 // 3.6V

Battery::Battery() : Threaded("Battery", 3 * 1024, 5), adc((gpio_num_t) PIN_BATT, 0.05, MIN_READ, MAX_READ, getVoltOffset()),
					 hysteresis({ 0, 4, 15, 30, 70, 100 }, 3),
					 chargeHyst(2000, false), sem(xSemaphoreCreateBinary()), timer(ShortMeasureIntverval, isr, sem){

	gpio_config_t cfg_gpio = {};
	cfg_gpio.mode = GPIO_MODE_INPUT;
	cfg_gpio.pull_down_en = GPIO_PULLDOWN_ENABLE;
	cfg_gpio.pull_up_en = GPIO_PULLUP_DISABLE;
	cfg_gpio.pin_bit_mask = 1ULL << PIN_CHARGE;
	cfg_gpio.intr_type = GPIO_INTR_POSEDGE;
	ESP_ERROR_CHECK(gpio_config(&cfg_gpio));

	checkCharging(true);
	sample(true); // this will initiate shutdown if battery is critical
}

Battery::~Battery(){
	gpio_set_intr_type((gpio_num_t) PIN_CHARGE, GPIO_INTR_DISABLE);
	gpio_isr_handler_remove((gpio_num_t) PIN_CHARGE);

	timer.stop();
	stop(0);
	abortFlag = true;
	xSemaphoreGive(sem);
	while(running()){
		vTaskDelay(1);
	}
}

void Battery::begin(){
	start();
	startTimer();
	gpio_isr_handler_add((gpio_num_t) PIN_CHARGE, isr, sem);
}

uint16_t Battery::mapRawReading(uint16_t reading){
	return std::round(map((double) reading, MIN_READ, MAX_READ, 3600, 4200));
}

int16_t Battery::getVoltOffset(){
	return 0;
	uint32_t upper = REG_GET_FIELD(EFUSE_BLK3_RDATA3_REG, EFUSE_RD_ADC1_TP_HIGH);
	uint32_t lower = REG_GET_FIELD(EFUSE_BLK3_RDATA3_REG, EFUSE_RD_ADC1_TP_LOW);
	return (upper << 7) | lower;
}

void Battery::checkCharging(bool fresh){
	if(shutdown) return;

	auto chrg = gpio_get_level((gpio_num_t) PIN_CHARGE) == 1;
	if(fresh){
		chargeHyst.reset(chrg);
	}else{
		chargeHyst.update(chrg);
	}

	if(isCharging()){
		if(!wasCharging){
			wasCharging = true;
			Events::post(Facility::Battery, Battery::Event{ .action = Event::Charging, .chargeStatus = true });
		}
	}else if(wasCharging){
		wasCharging = false;
		sample(true);
		Events::post(Facility::Battery, Battery::Event{ .action = Event::Charging, .chargeStatus = false });
	}
}

void Battery::sample(bool fresh){
	if(shutdown) return;
	if(isCharging()) return;

	auto level = getLevel();

	if(fresh){
		adc.resetEma();
		hysteresis.reset(adc.getVal());
	}else{
		auto val = adc.sample();
		hysteresis.update(val);
	}

	if(level != getLevel() || fresh){
		Events::post(Facility::Battery, Battery::Event{ .action = Event::LevelChange, .level = getLevel() });
	}

	if(level == Critical){
		shutdown = true;
		extern void shutdown();
		shutdown();
	}
}

void Battery::loop(){
	while(!xSemaphoreTake(sem, portMAX_DELAY)){
		timer.stop();
		startTimer();
	}
	timer.stop();

	if(abortFlag) return;

	std::lock_guard lock(mut);

	checkCharging();
	sample();

	startTimer();
}

void Battery::startTimer(){
	timer.stop();
	if(shutdown) return;

	if(isCharging() || !sleep){
		timer.setPeriod(ShortMeasureIntverval);
	}else{
		timer.setPeriod(LongMeasureIntverval);
	}
	timer.start();
}

void IRAM_ATTR Battery::isr(void* arg){
	BaseType_t priority = pdFALSE;
	xSemaphoreGiveFromISR(arg, &priority);
}

void Battery::setSleep(bool sleep){
	timer.stop();
	std::lock_guard lock(mut);
	this->sleep = sleep;
	xSemaphoreGive(sem);
}

uint8_t Battery::getPerc() const{
	return adc.getVal();
}

Battery::Level Battery::getLevel() const{
	return (Level) hysteresis.get();
}

bool Battery::isCharging() const{
	return chargeHyst.get();
}

bool Battery::isShutdown() const{
	return shutdown;
}
