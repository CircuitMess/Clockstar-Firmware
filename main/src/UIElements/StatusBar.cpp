#include "StatusBar.h"
#include "Util/Services.h"

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

	batPhone = new BatteryElement(left);
	phoneIcon = lv_img_create(left);

	if(showClock){
		clock = new ClockLabelSmall(*this);
		lv_obj_add_flag(*clock, LV_OBJ_FLAG_FLOATING);
		lv_obj_center(*clock);
	}

	batDevice = new BatteryElement(*this);

	// Events::listen(Facility::Phone, &queue); TODO: uncomment once evnet processing is actually hapening
	Events::listen(Facility::Battery, &queue);

	setPhoneConnected();
	setPhoneBattery();
	if(battery.isCharging()){
		batDevice->set(BatteryElement::Charging);
	}else if(battery.getPercentage() < 5){
		batDevice->set(BatteryElement::Empty);
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

	if(batPhone->getLevel() != 0 /*phone.battery*/){
		setPhoneBattery();
	}


	Event event{};
	if(queue.get(event, 0)){
		if(event.facility == Facility::Battery){
			auto data = (Battery::Event*) event.data;
			if(data->action == Battery::Event::BatteryLow){
				batDevice->set(BatteryElement::Empty);
			}else if(data->action == Battery::Event::Charging){
				if(data->chargeStatus){
					batDevice->set(BatteryElement::Charging);
				}else{
					setDeviceBattery();
				}
			}
		}
	}

	batDevice->loop();
	batPhone->loop();

	if(batDevice->getLevel() == BatteryElement::Charging) return;

	if(batDevice->getLevel() != getLevel(battery.getLevel())){
		setDeviceBattery();
	}
}

void StatusBar::setPhoneConnected(){
	connected = phone.isConnected();

	if(connected){
		lv_img_set_src(phoneIcon, "S:/icons/phone.bin");
		lv_obj_clear_flag(*batPhone, LV_OBJ_FLAG_HIDDEN);
	}else{
		lv_img_set_src(phoneIcon, "S:/icons/phoneDisconnected.bin");
		lv_obj_add_flag(*batPhone, LV_OBJ_FLAG_HIDDEN);
	}

	lv_obj_refr_size(left);
}

void StatusBar::setPhoneBattery(){
	batPhone->set(getLevel(0 /* phone level */));
}

void StatusBar::setDeviceBattery(){
	batDevice->set(getLevel(battery.getLevel()));
}

BatteryElement::Level StatusBar::getLevel(uint8_t level){
	if(level >= 3) return BatteryElement::Full;
	else if(level >= 2) return BatteryElement::Mid;
	else if(level >= 1) return BatteryElement::Low;
	else return BatteryElement::Empty;
}
