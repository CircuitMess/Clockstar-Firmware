#include "StatusBar.h"
#include "Util/Services.h"

StatusBar::StatusBar(lv_obj_t* parent, bool showClock) : LVObject(parent), phone(*((Phone*) Services.get(Service::Phone))), queue(12){
	lv_obj_set_size(*this, 128, 15);
	lv_obj_set_style_pad_ver(*this, 2, 0);
	lv_obj_set_style_pad_hor(*this, 3, 0);

	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	left = lv_obj_create(*this);
	lv_obj_set_size(left, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	lv_obj_set_style_pad_gap(left, 2, 0);
	lv_obj_set_flex_flow(left, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(left, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	batPhone = lv_img_create(left);
	phoneIcon = lv_img_create(left);

	if(showClock){
		clock = new ClockLabelSmall(*this);
		lv_obj_add_flag(*clock, LV_OBJ_FLAG_FLOATING);
		lv_obj_center(*clock);
	}

	batDevice = lv_img_create(*this);

	// Events::listen(Facility::Phone, &queue); TODO: uncomment once evnet processing is actually hapening

	setPhoneConnected();
	setPhoneBattery();
	setDeviceBattery();

	// TODO: blink battery icon when below 5% battery
	// TODO: play "charging" animation when charging - all level icons looped with ~500ms between them
}

void StatusBar::loop(){
	if(clock){
		clock->loop();
	}

	if(connected ^ phone.isConnected()){
		setPhoneConnected();
	}

	if(perBatPhone != 0 /*phone.battery*/){
		setPhoneBattery();
	}

	if(perBatDevice != 0 /*battery.perc*/){
		setDeviceBattery();
	}
}

void StatusBar::setPhoneConnected(){
	connected = phone.isConnected();

	if(connected){
		lv_img_set_src(phoneIcon, "S:/icons/phone.bin");
		lv_obj_clear_flag(batPhone, LV_OBJ_FLAG_HIDDEN);
	}else{
		lv_img_set_src(phoneIcon, "S:/icons/phoneDisconnected.bin");
		lv_obj_add_flag(batPhone, LV_OBJ_FLAG_HIDDEN);
	}

	lv_obj_refr_size(left);
}

void StatusBar::setPhoneBattery(){
	perBatPhone = 0; // phone.battery
	lv_img_set_src(batPhone, percentToIcon(perBatPhone));
}

void StatusBar::setDeviceBattery(){
	//TODO - use battery.getLevel() instead of getPercent()
	perBatDevice = 0; // phone.battery
	lv_img_set_src(batDevice, percentToIcon(perBatDevice));
}

const char* StatusBar::percentToIcon(uint8_t percent){
	if(percent >= 75) return "S:/icons/batteryFull.bin";
	else if(percent >= 25) return "S:/icons/batteryMid.bin";
	else return "S:/icons/batteryLow.bin";
}
