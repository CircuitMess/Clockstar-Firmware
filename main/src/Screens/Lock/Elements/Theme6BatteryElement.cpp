#include "Theme6BatteryElement.h"
#include "Util/Services.h"
#include "Theme/theme.h"

Theme6BatteryElement::Theme6BatteryElement(lv_obj_t* parent) : BatteryElement(parent){
	auto* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	batteryPercent = lv_label_create(*this);
	lv_obj_set_style_text_font(batteryPercent, &devin, 0); // TODO need a new font for this most likely
	lv_obj_set_style_text_color(batteryPercent, lv_color_make(255, 255, 0), 0);

	set(getLevel());
}

void Theme6BatteryElement::updateChargingVisuals(){
	// TODO put the lightning icon here in the future
}

void Theme6BatteryElement::updateLevelVisuals(){
	lv_label_set_text(batteryPercent, std::to_string(battery.getPerc()).c_str());
}

void Theme6BatteryElement::loop(){
	BatteryElement::loop();

	if(getLevel() != Charging){
		lv_obj_clear_flag(batteryPercent, LV_OBJ_FLAG_HIDDEN);
		lv_label_set_text(batteryPercent, std::to_string(battery.getPerc()).c_str());
	}else{
		lv_label_set_text(batteryPercent, "CHRG");
	}
}
