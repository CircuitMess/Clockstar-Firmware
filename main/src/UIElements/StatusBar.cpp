#include "StatusBar.h"

StatusBar::StatusBar(lv_obj_t* parent) : LVObject(parent){
	lv_obj_add_flag(*this, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_size(*this, Width, Height);
	lv_obj_set_style_pad_ver(*this, 1, 0);
	lv_obj_set_style_pad_right(*this, 3, 0);
	lv_obj_set_style_pad_left(*this, 3, 0);

	lv_style_set_text_font(textStyle, &lv_font_unscii_8);
	lv_style_set_text_color(textStyle, textColor);

	timeLabel = lv_label_create(*this);
	lv_obj_add_style(timeLabel, textStyle, 0);
	lv_obj_center(timeLabel);

	deviceBat = lv_img_create(*this);
	setDeviceBattery(100);
	lv_obj_align(deviceBat, LV_ALIGN_RIGHT_MID, 0, 0);

	phoneContainer = lv_obj_create(*this);
	lv_obj_set_size(phoneContainer, PhoneContainerWidth, PhoneContainerHeight);
	lv_obj_set_flex_flow(phoneContainer, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(phoneContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);

	phoneBat = lv_img_create(phoneContainer);
	setPhoneBattery(100);

	phoneStatus = lv_img_create(phoneContainer);
	setConnection(false);
}

void StatusBar::hideClock(){
	lv_obj_add_flag(timeLabel, LV_OBJ_FLAG_HIDDEN);
}

void StatusBar::setTime(uint8_t h, uint8_t m){
	lv_label_set_text_fmt(timeLabel, "%02d:%02d", h, m);
}

void StatusBar::setDeviceBattery(uint8_t percent){
	lv_img_set_src(deviceBat, percentToIcon(percent));
}


void StatusBar::setPhoneBattery(uint8_t percent){
	lv_img_set_src(phoneBat, percentToIcon(percent));
}

const char* StatusBar::percentToIcon(uint8_t percent){
	if(percent >= 75) return "S:/icons/batteryFull.bin";
	else if(percent >= 25) return "S:/icons/batteryMid.bin";
	else return "S:/icons/batteryLow.bin";
}

void StatusBar::setConnection(bool connected){
	lv_img_set_src(phoneStatus, connected ? "S:/icons/phone.bin" : "S:/icons/phoneDisconnected.bin");
	if(!connected){
		lv_obj_add_flag(phoneBat, LV_OBJ_FLAG_HIDDEN);
	}
}
