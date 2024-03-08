#include "BatteryElement.h"
#include "Util/stdafx.h"
#include "Util/Services.h"
#include "Settings/Settings.h"

BatteryElement::BatteryElement(lv_obj_t* parent) : LVObject(parent), battery(*(Battery*) Services.get(Service::Battery)), queue(6){
	lv_obj_set_size(*this, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	img = lv_img_create(*this);

	Events::listen(Facility::Battery, &queue);

	if(battery.isCharging()){
		set(BatteryElement::Charging);
		return;
	}

	auto lvl = battery.getLevel();
	if(lvl >= Battery::COUNT){
		set(BatteryElement::Full);
	}else if(lvl < Battery::VeryLow){
		set(BatteryElement::Empty);
	}else{
		set((BatteryElement::Level) (battery.getLevel() - 1));
	}
}

BatteryElement::~BatteryElement(){
	Events::unlisten(&queue);
}

void BatteryElement::loop(){
	Event event{};
	if(queue.get(event, 0)){
		if(event.facility == Facility::Battery){
			auto* battEvent = (Battery::Event*) event.data;

			if(battEvent->action == Battery::Event::Charging){
				if(battEvent->chargeStatus){
					set(BatteryElement::Charging);
				}
				free(event.data);
				return;
			}

			auto lvl = battEvent->level;
			if(lvl >= Battery::COUNT){
				set(BatteryElement::Full);
			}else if(lvl < Battery::VeryLow){
				set(BatteryElement::Empty);
			}else{
				set((BatteryElement::Level) (battery.getLevel() - 1));
			}
		}
		free(event.data);
	}

	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	const Theme theme = settings->get().themeData.theme;

	const char* BatteryIcons[] = {
			THEMED_FILE(Menu, BatteryEmpty, theme), THEMED_FILE(Menu, BatteryLow, theme), THEMED_FILE(Menu, BatteryMid, theme), THEMED_FILE(Menu, BatteryFull, theme)
	};

	if(level == Charging){
		if(millis() - chargingMillis > ChargingAnimTime){
			chargingIndex = (chargingIndex + 1) % BatteryLevels;
			chargingMillis = millis();
			lv_img_set_src(img, BatteryIcons[chargingIndex]);
		}
	}
}

void BatteryElement::updateVisuals(){
	set(level);
}

void BatteryElement::set(BatteryElement::Level level){
	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	const Theme theme = settings->get().themeData.theme;

	const char* BatteryIcons[] = {
			THEMED_FILE(Menu, BatteryEmpty, theme), THEMED_FILE(Menu, BatteryLow, theme), THEMED_FILE(Menu, BatteryMid, theme), THEMED_FILE(Menu, BatteryFull, theme)
	};

	this->level = level;
	if(level == Charging){
		chargingMillis = millis();
		chargingIndex = 0;
		lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
		lv_img_set_src(img, BatteryIcons[1]);
	}else{
		lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
		lv_img_set_src(img, BatteryIcons[level]);
	}
}