#include "StatusBar.h"
#include "Util/Services.h"
#include "Filepaths.hpp"
#include "Settings/Settings.h"

StatusBar::StatusBar(lv_obj_t* parent, bool showExtra) : LVObject(parent), phone(*((Phone*) Services.get(Service::Phone))),
														 battery(*((Battery*) Services.get(Service::Battery))), queue(12), showExtra(showExtra){
	buildUI();

	// Events::listen(Facility::Phone, &queue); TODO: uncomment once evnet processing is actually hapening
	Events::listen(Facility::Battery, &queue);

	setPhoneConnected();
	setDeviceBattery();
}

StatusBar::~StatusBar(){
	Events::unlisten(&queue);
}

void StatusBar::loop(){
	if(clock){
		clock->loop();
	}

	if(connected ^ phone.isConnected()){
		setPhoneConnected();
	}

	if(showExtra && notifPresent ^ (phone.getNotifsCount() > 0)){
		setNotifIcon();
	}

	Event event{};
	if(queue.get(event, 0)){
		if(event.facility == Facility::Battery){
			setDeviceBattery();
		}
		free(event.data);
	}

	batDevice->loop();
}

void StatusBar::setPhoneConnected(){
	connected = phone.isConnected();

	if(connected){
		lv_img_set_src(phoneIcon, File::Menu::Default::Phone);
	}else{
		lv_img_set_src(phoneIcon, File::Menu::Default::PhoneDisconnected);
	}

	lv_obj_refr_size(left);
}

void StatusBar::setDeviceBattery(){
	if(battery.isCharging()){
		batDevice->set(BatteryElement::Charging);
		return;
	}

	auto level = battery.getLevel();
	if(level >= Battery::COUNT){
		batDevice->set(BatteryElement::Full);
	}else if(level < Battery::VeryLow){
		batDevice->set(BatteryElement::Empty);
	}else{
		batDevice->set((BatteryElement::Level) (battery.getLevel() - 1));
	}
}

void StatusBar::setNotifIcon(){
	if(phone.getNotifsCount()){
		lv_obj_clear_flag(notifIcon, LV_OBJ_FLAG_HIDDEN);
		notifPresent = true;
	}else{
		lv_obj_add_flag(notifIcon, LV_OBJ_FLAG_HIDDEN);
		notifPresent = false;
	}
}

void StatusBar::buildUI(){
	lv_obj_set_size(*this, 128, 15);
	lv_obj_set_style_pad_ver(*this, 2, 0);
	lv_obj_set_style_pad_hor(*this, 4, 0);

	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	left = lv_obj_create(*this);
	lv_obj_set_size(left, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	lv_obj_set_style_pad_gap(left, 2, 0);
	lv_obj_set_flex_flow(left, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(left, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	right = lv_obj_create(*this);
	lv_obj_set_size(right, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	lv_obj_set_style_pad_gap(right, 2, 0);

	lv_obj_set_flex_flow(right, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(right, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	if(showExtra){
		clock = new ClockLabelSmall(*this);
		lv_obj_add_flag(*clock, LV_OBJ_FLAG_FLOATING);
		lv_obj_center(*clock);

		notifIcon = lv_img_create(right);

		Settings* settings = (Settings*) Services.get(Service::Settings);
		if(settings == nullptr){
			return;
		}

		const Theme theme = settings->get().theme.theme;

		lv_img_set_src(notifIcon, THEMED_FILE(Icons, CatOther, theme));
		setNotifIcon();
	}

	phoneIcon = lv_img_create(right);

	delete batDevice;
	batDevice = new BatteryElement(left);
}
