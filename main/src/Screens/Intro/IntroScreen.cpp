#include "IntroScreen.h"
#include "Util/stdafx.h"
#include "Screens/Lock/LockScreen.h"
#include "Filepaths.hpp"

IntroScreen::IntroScreen(){
	bg = lv_obj_create(*this);
	lv_obj_set_style_bg_img_opa(bg, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(bg, File::Intro::OrangeBackground, 0);
	lv_obj_move_background(bg);
	lv_obj_add_flag(bg, LV_OBJ_FLAG_FLOATING);

	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	for(int i = 0; i < 3; ++i){
		imageConts[i] = lv_obj_create(*this);
		lv_obj_set_size(imageConts[i], 128, 128);
		images[i] = lv_img_create(imageConts[i]);
		lv_img_set_src(images[i], ImagePaths[i]);
		lv_obj_center(images[i]);
	}
}

void IntroScreen::loop(){
	if(state == Scrolling && millis() - counter >= ScrollTime){
		state = Waiting;
		counter = millis();
	}else if(state == Waiting && millis() - counter >= WaitTime){
		currentIndex++;
		if(currentIndex >= 2){
			transition([](){ return std::make_unique<LockScreen>(); });
			return;
		}
		state = Scrolling;
		counter = millis();
		const auto currentScroll =  lv_obj_get_scroll_y(*this);
		lv_anim_set_values(&anim, currentScroll, currentScroll +  128);
		lv_anim_start(&anim);
	}
}

void IntroScreen::onStart(){
	counter = millis();
	lv_anim_init(&anim);
	lv_anim_set_exec_cb(&anim, animFunc);
	lv_anim_set_var(&anim, *this);
	lv_anim_set_time(&anim, ScrollTime);
	lv_anim_set_path_cb(&anim, lv_anim_path_ease_in_out);
}

void IntroScreen::animFunc(void* obj, int32_t val){
	lv_obj_scroll_to_y((lv_obj_t*)obj, val, LV_ANIM_OFF);
}

void IntroScreen::onStop(){
	lv_anim_del(*this, nullptr);
}
