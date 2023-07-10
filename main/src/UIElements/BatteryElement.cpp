#include "BatteryElement.h"
#include "Util/stdafx.h"

BatteryElement::BatteryElement(lv_obj_t* parent) : LVObject(parent){
	lv_obj_set_size(*this, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	img = lv_img_create(*this);
}

void BatteryElement::set(BatteryElement::Level level){
	this->level = level;
	if(level == Empty){
		lowBatteryAnimToggle = true;
		lowBatMillis = millis();
		lv_img_set_src(img, "S:/icons/batteryLow.bin");
	}else if(level == Charging){
		chargingMillis = millis();
		chargingIndex = 0;
		lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
		lv_img_set_src(img, "S:/icons/batteryLow.bin");
	}else{
		lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
		lv_img_set_src(img, BatteryIcons[level - 1]);
	}
}

void BatteryElement::loop(){
	if(level == Charging){
		if(millis() - chargingMillis > ChargingAnimTime){
			chargingIndex = (chargingIndex + 1) % BatteryLevels;
			chargingMillis = millis();
			lv_img_set_src(img, BatteryIcons[chargingIndex]);
		}
	}else if(level == Empty){
		if(millis() - lowBatMillis > LowBatteryAnimTime){
			lowBatMillis = millis();
			if(lowBatteryAnimToggle){
				lv_obj_clear_flag(img, LV_OBJ_FLAG_HIDDEN);
			}else{
				lv_obj_add_flag(img, LV_OBJ_FLAG_HIDDEN);
			}
			lowBatteryAnimToggle = !lowBatteryAnimToggle;
		}
	}
}

BatteryElement::Level BatteryElement::getLevel() const{
	return level;
}
