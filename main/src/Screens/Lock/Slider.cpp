#include <cmath>
#include "Slider.h"
#include "Util/stdafx.h"
#include "Filepaths.hpp"

Slider::Slider(lv_obj_t* parent) : LVObject(parent){
	lv_obj_set_size(*this, 128, 16);

	icon = lv_img_create(*this);
	lv_img_set_src(icon, File::Icons::Default::LockClosed);
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
		lv_obj_set_pos(icon, 6 + std::round(128.0f * t()), LockY);
		return;
	}

	if(millis() - activityTime >= InactivityTimeout){
		hide();
	}
}

void Slider::start(){
	if(startTime != 0) return;

	startTime = millis();
	lv_obj_clear_flag(icon, LV_OBJ_FLAG_HIDDEN);
	lv_img_set_src(icon, File::Icons::Default::LockOpen);
}

void Slider::stop(){
	if(startTime == 0) return;

	startTime = 0;
	lv_img_set_src(icon, File::Icons::Default::LockClosed);
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
