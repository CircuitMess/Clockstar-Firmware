#include <cmath>
#include "Slider.h"
#include "Util/stdafx.h"

Slider::Slider(lv_obj_t* parent) : LVObject(parent){
	lv_obj_set_size(*this, 128, 16);

	icon = lv_img_create(*this);
	lv_img_set_src(icon, "S:/icon/lock_closed.bin");
	lv_obj_set_pos(icon, 6, 0);
}

bool Slider::started(){
	return startTime != 0;
}

float Slider::t(){
	if(startTime == 0) return 0;
	return (float) (millis() - startTime) / (float) Duration;
}

void Slider::loop(){
	if(timeout == -1){
		timeout = millis();
	}

	if(millis() - timeout >= InactivityTimeout && !hidden){
		lv_obj_add_flag(icon, LV_OBJ_FLAG_HIDDEN);
		hidden = true;
	}

	if(startTime == 0) return;
	lv_obj_set_pos(icon, 6 + std::round(128.0f * t()), 0);
}

void Slider::start(){
	if(startTime != 0) return;

	if(hidden){
		activity();
	}

	startTime = millis();
	lv_img_set_src(icon, "S:/icon/lock_open.bin");
}

void Slider::stop(){
	if(startTime == 0) return;

	startTime = 0;
	lv_img_set_src(icon, "S:/icon/lock_closed.bin");
	lv_obj_set_pos(icon, 6, 0);
}

void Slider::activity(){
	timeout = millis();
	if(hidden){
		lv_obj_clear_flag(icon, LV_OBJ_FLAG_HIDDEN);
		hidden = false;
	}
}
