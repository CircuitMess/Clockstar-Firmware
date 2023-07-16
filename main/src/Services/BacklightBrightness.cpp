#include "BacklightBrightness.h"
#include <algorithm>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include "Util/Services.h"
#include "Util/stdafx.h"

BacklightBrightness::BacklightBrightness(PWM* pwm) : pwm(*pwm){

}

void BacklightBrightness::setBrightness(uint8_t level){
	pwm.setDuty(mapDuty(level));
}

constexpr uint8_t BacklightBrightness::mapDuty(uint8_t level){
	level = std::clamp(level, (uint8_t) 0, (uint8_t) 100);
	level = map(level, 0, 100, MinDuty, 100);
	return level;
}

void BacklightBrightness::fadeIn(){
	Settings& settings = *(Settings*) Services.get(Service::Settings);

	for(uint8_t i = 0; i < 100; i++){
		uint8_t val = map(i, 0, 100, 0, mapDuty(settings.get().screenBrightness));
		pwm.setDuty(val);
		vTaskDelay(FadeDelay / portTICK_PERIOD_MS);
	}
}

void BacklightBrightness::fadeOut(){
	Settings& settings = *(Settings*) Services.get(Service::Settings);

	for(uint8_t i = 100; i > 0; i--){
		uint8_t val = map(i, 0, 100, 0, mapDuty(settings.get().screenBrightness));
		pwm.setDuty(val);
		vTaskDelay(FadeDelay / portTICK_PERIOD_MS);
	}
}