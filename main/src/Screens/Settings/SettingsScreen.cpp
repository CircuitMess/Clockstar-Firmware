#include "SettingsScreen.h"
#include "Devices/Input.h"
#include "Util/Services.h"
#include "Screens/MainMenu/MainMenu.h"
#include "BoolElement.h"
#include "SliderElement.h"
#include "LabelElement.h"
#include "DiscreteSliderElement.h"

SettingsScreen::SettingsScreen() : settings(*(Settings*) Services.get(Service::Settings)), backlight(*(BacklightBrightness*) Services.get(Service::Backlight)),
								   audio(*(ChirpSystem*) Services.get(Service::Audio)), queue(4){
	lv_obj_set_size(*this, 128, 128);

	bg = lv_obj_create(*this);
	lv_obj_add_flag(bg, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_size(bg, 128, 256);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", 0);

	container = lv_obj_create(*this);
	lv_obj_set_size(container, 128, 128 - TopPadding);
	lv_obj_set_pos(container, 0, TopPadding);
	lv_obj_add_flag(container, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(container, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_gap(container, 5, 0);

	statusBar = new StatusBar(*this);
	lv_obj_add_flag(*statusBar, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_pos(*statusBar, 0, 0);

	auto startingSettings = settings.get();

	audioSwitch = new BoolElement(container, "Sound", [this](bool value){
		audio.setMute(!audioSwitch->getValue());
		if(value){
			audio.play({ { 523, 523, 50 } });
		}
	}, startingSettings.notificationSounds);
	lv_group_add_obj(inputGroup, *audioSwitch);

	brightnessSlider = new SliderElement(container, "Brightness", [this](uint8_t value){
		backlight.setBrightness(value);
	}, startingSettings.screenBrightness);
	lv_group_add_obj(inputGroup, *brightnessSlider);

	ledSwitch = new BoolElement(container, "LED enable", [this](bool value){
		//TODO - apply LED toggle
		if(value){
			//TODO - blink LED
		}
	}, startingSettings.notificationSounds);
	lv_group_add_obj(inputGroup, *ledSwitch);

	sleepSlider = new DiscreteSliderElement(container, "Sleep time", [this](uint8_t value){
		//TODO - apply sleep if necessary
	}, std::vector<const char*>(Settings::SleepText, Settings::SleepText + Settings::SleepSteps), startingSettings.sleepTime);
	lv_group_add_obj(inputGroup, *sleepSlider);

	saveAndExit = new LabelElement(container, "Save and Exit", [this](){
		transition([](){ return std::make_unique<MainMenu>(); });
	});
	lv_group_add_obj(inputGroup, *saveAndExit);

	for(int i = 0; i < lv_obj_get_child_cnt(container); ++i){
		lv_obj_add_flag(lv_obj_get_child(container, i), LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	}
}

void SettingsScreen::loop(){
	Event evt{};
	if(queue.get(evt, 0)){
		if(evt.facility == Facility::Input){
			auto eventData = (Input::Data*) evt.data;
			if(eventData->btn == Input::Alt && eventData->action == Input::Data::Press){
				free(evt.data);
				transition([](){ return std::make_unique<MainMenu>(); });
				return;
			}
		}
		free(evt.data);
	}

	statusBar->loop();
}

void SettingsScreen::onStop(){
	auto savedSettings = settings.get();
	savedSettings.notificationSounds = audioSwitch->getValue();
	savedSettings.screenBrightness = brightnessSlider->getValue();
	savedSettings.sleepTime = sleepSlider->getValue();
	savedSettings.ledEnable = ledSwitch->getValue();
	settings.set(savedSettings);

	backlight.setBrightness(brightnessSlider->getValue());
	audio.setMute(!savedSettings.notificationSounds);

	//TODO - apply sleep time
	//TODO - apply LED toggle

	Events::unlisten(&queue);
}

void SettingsScreen::onStarting(){
	brightnessSlider->setValue(settings.get().screenBrightness);
	audioSwitch->setValue(settings.get().notificationSounds);
	ledSwitch->setValue(settings.get().ledEnable);
	sleepSlider->setValue(settings.get().sleepTime);
}

void SettingsScreen::onStart(){
	Events::listen(Facility::Input, &queue);
}
