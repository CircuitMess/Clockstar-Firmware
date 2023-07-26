#include "BacklightBrightness.h"
#include <algorithm>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <cmath>
#include "Util/Services.h"
#include "Util/stdafx.h"

BacklightBrightness::BacklightBrightness(PWM* pwm) : pwm(*pwm){

}

void BacklightBrightness::setBrightness(uint8_t level){
	pwm.setDuty(mapDuty(level));
}

constexpr uint8_t BacklightBrightness::mapDuty(uint8_t level){
	level = std::clamp(level, (uint8_t) 0, (uint8_t) 100);

	double fVal = (float) level / 100.0f;
	fVal = std::pow(fVal, 2);
	fVal = std::round(fVal * 100.0f);

	fVal = map(fVal, 0, 100, MinDuty, 100);

	return (uint8_t)fVal;
}

void BacklightBrightness::fadeIn(){
	if(state) return;
	state = true;

	pwm.attach();
	Settings& settings = *(Settings*) Services.get(Service::Settings);

	for(uint8_t i = 0; i < 100; i++){
		uint8_t val = map(i, 0, 100, 0, mapDuty(settings.get().screenBrightness));
		pwm.setDuty(val);
		vTaskDelay(FadeDelay / portTICK_PERIOD_MS);
	}
}

void BacklightBrightness::fadeOut(){
	if(!state) return;
	state = false;

	Settings& settings = *(Settings*) Services.get(Service::Settings);

	for(uint8_t i = 100; i > 0; i--){
		uint8_t val = map(i, 0, 100, 0, mapDuty(settings.get().screenBrightness));
		pwm.setDuty(val);
		vTaskDelay(FadeDelay / portTICK_PERIOD_MS);
	}
	pwm.detach();
}

bool BacklightBrightness::isOn(){
	return state;
}
