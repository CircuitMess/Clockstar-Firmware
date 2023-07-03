#include "StatusBar.h"
#include "Util/Services.h"
#include "Util/stdafx.h"

StatusBar::StatusBar(lv_obj_t* parent, bool showClock) : LVObject(parent), phone(*((Phone*) Services.get(Service::Phone))),
														 battery(*((Battery*) Services.get(Service::Battery))), queue(12){
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
		clock = new ClockLabel(*this);
		lv_obj_add_flag(*clock, LV_OBJ_FLAG_FLOATING);
		lv_obj_center(*clock);
	}

	right = lv_obj_create(*this);
	lv_obj_set_size(right, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	batDevice = lv_img_create(right);

	// Events::listen(Facility::Phone, &queue); TODO: uncomment once evnet processing is actually hapening
	Events::listen(Facility::Battery, &queue);

	setPhoneConnected();
	setPhoneBattery();
	if(battery.isCharging()){
		chargingEvent(true);
	}else if(battery.getPercentage() < 5){
		lowBatteryEvent();
	}else{
		setDeviceBattery();
	}
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


	Event event{};
	if(queue.get(event, 0)){
		if(event.facility == Facility::Battery){
			auto data = (Battery::Event*) event.data;
			if(data->action == Battery::Event::BatteryLow){
				lowBatteryEvent();
			}else if(data->action == Battery::Event::Charging){
				chargingEvent(data->chargeStatus);
			}
		}
	}

	if(chargingAnimation){
		if(millis() - chargingMillis > ChargingAnimTime){
			chargingIndex = (chargingIndex + 1) % BatteryLevels;
			chargingMillis = millis();
			lv_img_set_src(batDevice, BatteryIcons[chargingIndex]);
		}
		return;
	}

	if(lowBatteryAnimation){
		if(millis() - lowBatMillis > LowBatteryAnimTime){
			lowBatMillis = millis();
			if(lowBatteryAnimToggle){
				lv_obj_clear_flag(batDevice, LV_OBJ_FLAG_HIDDEN);
			}else{
				lv_obj_add_flag(batDevice, LV_OBJ_FLAG_HIDDEN);
			}
			lowBatteryAnimToggle = !lowBatteryAnimToggle;
		}
		return;
	}

	if(battery.getPercentage() != 0){
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
	perBatDevice = battery.getPercentage();
	lv_img_set_src(batDevice, percentToIcon(perBatDevice));
}

const char* StatusBar::percentToIcon(uint8_t percent){
	if(percent >= 75) return "S:/icons/batteryFull.bin";
	else if(percent >= 25) return "S:/icons/batteryMid.bin";
	else return "S:/icons/batteryLow.bin";
}

void StatusBar::chargingEvent(bool chargeStatus){
	chargingAnimation = chargeStatus;
	if(!chargeStatus){
		lowBatteryAnimToggle = true;
		lowBatMillis = millis();
		setDeviceBattery();
	}else{
		chargingMillis = millis();
		chargingIndex = 0;
		lv_obj_clear_flag(batDevice, LV_OBJ_FLAG_HIDDEN);
		lv_img_set_src(batDevice, "S:/icons/batteryLow.bin");
	}
}

void StatusBar::lowBatteryEvent(){
	lowBatteryAnimation = true;
	lowBatteryAnimToggle = true;
	lowBatMillis = millis();
	lv_img_set_src(batDevice, "S:/icons/batteryLow.bin");
}
