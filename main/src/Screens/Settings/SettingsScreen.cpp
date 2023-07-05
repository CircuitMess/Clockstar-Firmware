#include "SettingsScreen.h"
#include "Devices/Input.h"
#include "Util/Services.h"
#include "Screens/MainMenu/MainMenu.h"
#include "BoolElement.h"
#include "SliderElement.h"

SettingsScreen::SettingsScreen() : settings(*(Settings*) Services.get(Service::Settings)), queue(4){
	lv_obj_set_size(*this, 128, LV_SIZE_CONTENT);

	statusBar = new StatusBar(*this);
	lv_obj_add_flag(*statusBar, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_pos(*statusBar, 0, 0);

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


	auto startingSettings = settings.get();

	audio = new BoolElement(container, "Sound", [this](bool value){
		printf("value changed %d\n", value);
		if(value){
			//TODO - set audio mute/unmute
			//TODO - add piezo beep on toggle     tone(NOTE_C5, 25);
		}
	}, startingSettings.notificationSounds);
	lv_group_add_obj(inputGroup, *audio);

	brightness = new SliderElement(container, "Brightness", [this](bool value){
		//TODO - set brightness
	}, startingSettings.screenBrightness);
	lv_group_add_obj(inputGroup, *brightness);

	Events::listen(Facility::Input, &queue);
}

void SettingsScreen::loop(){
	statusBar->loop();

	Event evt;
	if(queue.get(evt, 0)){
		if(evt.facility == Facility::Input){
			auto data = (Input::Data*) evt.data;
			if(data->btn == Input::Alt && data->action == Input::Data::Press){
				delete data;
				transition([](){ return std::make_unique<MainMenu>(); });
				return;
			}
		}
	}
}

void SettingsScreen::onStop(){
	auto savedSettings = settings.get();
	savedSettings.notificationSounds = audio->getValue();
	savedSettings.screenBrightness = brightness->getValue();
	settings.set(savedSettings);
	//TODO - apply settings
}

