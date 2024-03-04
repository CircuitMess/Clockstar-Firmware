#include "PhoneElement.h"
#include "Util/Services.h"
#include "Filepaths.hpp"
#include "Settings/Settings.h"

PhoneElement::PhoneElement(lv_obj_t* parent, bool showNotifIcon) : LVObject(parent), showNotifIcon(showNotifIcon),
																   phone(*((Phone*) Services.get(Service::Phone))){
	auto* settings = (Settings*) Services.get(Service::Settings);
	phonePath = THEMED_FILE(Menu, Phone, settings->get().theme.theme);
	phoneDcPath = THEMED_FILE(Menu, PhoneDisconnected, settings->get().theme.theme);
	notifPath = THEMED_FILE(Icons, CatOther, settings->get().theme.theme);

	lv_obj_set_size(*this, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	lv_obj_set_style_pad_gap(*this, 3, 0);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_layout(*this, LV_LAYOUT_FLEX);

	if(showNotifIcon){
		notifIcon = lv_img_create(*this);
		lv_img_set_src(notifIcon, notifPath);
		setNotifIcon();
	}
	phoneIcon = lv_img_create(*this);
	setPhoneConnected();
}

void PhoneElement::loop(){
	if(connected ^ phone.isConnected()){
		setPhoneConnected();
	}

	if(showNotifIcon && notifPresent ^ (phone.getNotifsCount() > 0)){
		setNotifIcon();
	}
}

void PhoneElement::setPhoneConnected(){
	connected = phone.isConnected();

	if(connected){
		lv_img_set_src(phoneIcon, phonePath);
	}else{
		lv_img_set_src(phoneIcon, phoneDcPath);
	}
}

void PhoneElement::setNotifIcon(){
	if(phone.getNotifsCount()){
		lv_obj_clear_flag(notifIcon, LV_OBJ_FLAG_HIDDEN);
		notifPresent = true;
	}else{
		lv_obj_add_flag(notifIcon, LV_OBJ_FLAG_HIDDEN);
		notifPresent = false;
	}
}
