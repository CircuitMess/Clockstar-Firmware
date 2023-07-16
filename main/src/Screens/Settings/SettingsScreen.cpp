#include "SettingsScreen.h"
#include "Devices/Input.h"
#include "Util/Services.h"
#include "Screens/MainMenu/MainMenu.h"
#include "BoolElement.h"
#include "SliderElement.h"
#include "LabelElement.h"

SettingsScreen::SettingsScreen() : settings(*(Settings*) Services.get(Service::Settings)), backlight(*(BacklightBrightness*) Services.get(Service::Backlight)),
								   audio(*(ChirpSystem*) Services.get(Service::Audio)){
	lv_obj_set_size(*this, 128, LV_SIZE_CONTENT);


	bg = lv_obj_create(*this);
	lv_obj_add_flag(bg, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_size(bg, 128, 256);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", 0);

	container = lv_obj_create(*this);
	lv_obj_set_size(container, 128, LV_SIZE_CONTENT);
	lv_obj_add_flag(container, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_top(container, 20, 0);
	lv_obj_set_style_pad_gap(container, 5, 0);

	statusBar = new StatusBar(*this);
	lv_obj_add_flag(*statusBar, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_pos(*statusBar, 0, 0);

	auto startingSettings = settings.get();

	audioSwitch = new BoolElement(container, "Sound", [this](bool value){
		audio.setMute(!audioSwitch->getValue());
		if(value){
			audio.play({ { 523, 523, 25 } });
		}
	}, startingSettings.notificationSounds);
	lv_group_add_obj(inputGroup, *audioSwitch);

	brightnessSlider = new SliderElement(container, "Brightness", [this](uint8_t value){
		backlight.setBrightness(value);
	}, startingSettings.screenBrightness);
	lv_group_add_obj(inputGroup, *brightnessSlider);

	saveAndExit = new LabelElement(container, "Save and Exit", [this](){
		transition([](){ return std::make_unique<MainMenu>(); });
	});
	lv_group_add_obj(inputGroup, *saveAndExit);
}

void SettingsScreen::loop(){
	statusBar->loop();
}

void SettingsScreen::onStop(){
	auto savedSettings = settings.get();
	savedSettings.notificationSounds = audioSwitch->getValue();
	savedSettings.screenBrightness = brightnessSlider->getValue();
	settings.set(savedSettings);

	backlight.setBrightness(brightnessSlider->getValue());
	audio.setMute(!savedSettings.notificationSounds);
}

void SettingsScreen::onStarting(){
	brightnessSlider->setValue(settings.get().screenBrightness);
	audioSwitch->setValue(settings.get().notificationSounds);
}
