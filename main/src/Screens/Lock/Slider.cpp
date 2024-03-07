#include <cmath>
#include "Slider.h"
#include "Util/stdafx.h"
#include "Filepaths.hpp"
#include "Settings/Settings.h"
#include "Util/Services.h"

Slider::Slider(lv_obj_t* parent, bool reverse) : LVObject(parent), reverse(reverse){
	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	const Theme theme = settings->get().themeData.theme;

	lv_obj_set_size(*this, 128, 16);

	icon = lv_img_create(*this);
	lv_img_set_src(icon, THEMED_FILE(Icons, LockClosed, theme));
	lv_obj_set_pos(icon, 6, LockY);
}

bool Slider::started(){
	return startTime != 0;
}

float Slider::t(){
	if(startTime == 0) return 0;
	return (float) (millis() - startTime) / (float) Duration;
}

void Slider::loop(){
	if(startTime == 0 && activityTime == 0) return;

	if(startTime != 0){
		if(reverse){
			lv_obj_set_pos(icon, 128 - 6 - std::round(128.0f * t()), LockY);
		}else{
			lv_obj_set_pos(icon, 6 + std::round(128.0f * t()), LockY);
		}

		return;
	}

	if(millis() - activityTime >= InactivityTimeout){
		hide();
	}
}

void Slider::start(){
	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	const Theme theme = settings->get().themeData.theme;

	if(startTime != 0) return;

	startTime = millis();
	lv_obj_clear_flag(icon, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(icon, THEMED_FILE(Icons, LockOpen, theme));
}

void Slider::stop(){
	if(startTime == 0) return;

	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	const Theme theme = settings->get().themeData.theme;

	startTime = 0;
	lv_img_set_src(icon, THEMED_FILE(Icons, LockClosed, theme));
	lv_obj_set_pos(icon, 6, LockY);

	activity();
}

void Slider::activity(){
	activityTime = millis();
	lv_obj_clear_flag(icon, LV_OBJ_FLAG_HIDDEN);
}

void Slider::hide(){
	activityTime = 0;
	lv_obj_add_flag(icon, LV_OBJ_FLAG_HIDDEN);
}
