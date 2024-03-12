#include "Theme9BatteryElement.h"
#include "Util/Services.h"
#include "Theme/theme.h"

Theme9BatteryElement::Theme9BatteryElement(lv_obj_t* parent) : BatteryElement(parent){
	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	batteryPercent = lv_label_create(*this);
	lv_obj_set_style_text_font(batteryPercent, &devin, 0); // TODO need a new font for this most likely
	lv_obj_set_style_text_color(batteryPercent, lv_color_white(), 0);

	set(getLevel());
}

void Theme9BatteryElement::updateChargingVisuals(){
	// TODO put lightning icon when this gets called
}

void Theme9BatteryElement::updateLevelVisuals(){
	lv_label_set_text(batteryPercent, std::to_string(battery.getPerc()).c_str());
}

void Theme9BatteryElement::loop(){
	BatteryElement::loop();

	if(getLevel() != Charging){
		lv_obj_clear_flag(batteryPercent, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(batteryPercent, std::to_string(battery.getPerc()).c_str());
	}else{
		lv_label_set_text(batteryPercent, "CHRG");
	}
}
