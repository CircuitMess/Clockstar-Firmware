#include "MainMenu.h"
#include "Util/Services.h"
#include "MenuItemAlt.h"
#include "Screens/Lock/LockScreen.h"
#include "Screens/Level.h"
#include "Screens/Theremin/Theremin.h"
#include "Screens/Settings/SettingsScreen.h"
#include "Util/stdafx.h"

uint8_t  MainMenu::lastIndex = 0;

MainMenu::MainMenu() : phone(*((Phone*) Services.get(Service::Phone))), queue(4){
	lv_img_cache_set_size(8);

	lv_obj_set_size(*this, 128, LV_SIZE_CONTENT);
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	bg = lv_obj_create(*this);
	lv_obj_add_flag(bg, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_size(bg, 128, 128);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", 0);

	for(int i = 0; i < ItemCount; i++){
		// TODO: connected/disconnected alt labels for phone connection
		// TODO: add "Press to stop" to ringing alt label
		if(i == 0){
			auto item = new MenuItemAlt(*this, ItemInfos[i].iconPath, ItemInfos[i].labelPath);
			item->setAltLabel(AltItems[i].iconPath, getConnectionDesc(phone.getPhoneType()));
			items[i] = item;
			phoneConnection = item;
		}else if(i < AltItemCount){
			auto item = new MenuItemAlt(*this, ItemInfos[i].iconPath, ItemInfos[i].labelPath);
			item->setAltPaths(AltItems[i].iconPath, AltItems[i].labelPath);
			items[i] = item;
		}else{
			items[i] = new MenuItem(*this, ItemInfos[i].iconPath, ItemInfos[i].labelPath);

			lv_obj_add_event_cb(*items[i], [](lv_event_t* evt){
				auto menu = static_cast<MainMenu*>(evt->user_data);
				menu->onClick();
			}, LV_EVENT_CLICKED, this);
		}

		lv_group_add_obj(inputGroup, *items[i]);
		lv_obj_add_flag(*items[i], LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(*items[i], LV_OBJ_FLAG_SNAPPABLE);
		lv_obj_clear_flag(*items[i], LV_OBJ_FLAG_CLICK_FOCUSABLE);
	}

	//find my phone
	lv_obj_add_event_cb(*items[1], [](lv_event_t* evt){
		auto menu = static_cast<MainMenu*>(evt->user_data);
		if(menu->findPhoneRinging){
			menu->stopPhoneRing();
		}else{
			menu->startPhoneRing();
		}
	}, LV_EVENT_CLICKED, this);

	lv_obj_add_event_cb(*items[1], [](lv_event_t* evt){
		auto menu = static_cast<MainMenu*>(evt->user_data);
		if(menu->findPhoneRinging){
			menu->stopPhoneRing();
		}
	}, LV_EVENT_DEFOCUSED, this);

	statusBar = new StatusBar(*this);
	lv_obj_add_flag(*statusBar, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_pos(*statusBar, 0, 0);

	// Scrolling
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLL_ONE);
	lv_obj_set_scroll_snap_y(*this, LV_SCROLL_SNAP_START);
	lv_group_set_wrap(inputGroup, false);

	Events::listen(Facility::Input, &queue);
	Events::listen(Facility::Phone, &queue);
}

MainMenu::~MainMenu(){
	Events::unlisten(&queue);
	lv_img_cache_set_size(LV_IMG_CACHE_DEF_SIZE);
}

void MainMenu::onStarting(){
	if(phone.getPhoneType() != Phone::PhoneType::Android){
		lv_obj_add_flag(*items[1], LV_OBJ_FLAG_HIDDEN);
	}

	lv_group_focus_obj(*items[lastIndex]);
	lv_obj_scroll_to_view(*items[lastIndex], LV_ANIM_OFF);
}

void MainMenu::onStop(){
	findPhoneRinging = false;
	phone.findPhoneStop();
}

void MainMenu::loop(){
	statusBar->loop();

	handleRing();

	Event evt;
	if(queue.get(evt, 0)){
		if(evt.facility == Facility::Input){
			auto data = (Input::Data*) evt.data;
			handleInput(*data);
		}else if(evt.facility == Facility::Phone){
			auto data = (Phone::Event*) evt.data;
			handlePhoneChange(*data);
		}
		free(evt.data);
	}
}

void MainMenu::onClick(){
	auto focused = lv_group_get_focused(inputGroup);
	auto index = lv_obj_get_index(focused);
	if(index <= AltItemCount) return;

	lastIndex = index - 1;

	std::function<void()> launcher[] = {
			[this](){ transition([](){ return std::make_unique<Level>(); }); },
			[this](){ transition([](){ return std::make_unique<Theremin>(); }); },
			[this](){ transition([](){ return std::make_unique<SettingsScreen>(); }); }
	};

	launcher[index - AltItemCount - 1]();
}

void MainMenu::handlePhoneChange(Phone::Event& event){
	auto focused = lv_group_get_focused(inputGroup);
	auto index = lv_obj_get_index(focused);
	auto& findPhone = *items[1];
	bool hiddenBefore = lv_obj_has_flag(findPhone, LV_OBJ_FLAG_HIDDEN);

	if(event.action == Phone::Event::Connected || event.action == Phone::Event::Disconnected){
		if(event.data.phoneType == Phone::PhoneType::Android && event.action == Phone::Event::Connected){
			lv_obj_clear_flag(findPhone, LV_OBJ_FLAG_HIDDEN);
		}else{
			lv_obj_add_flag(findPhone, LV_OBJ_FLAG_HIDDEN);
		}
		phoneConnection->setAltLabel(AltItems[0].iconPath, getConnectionDesc(phone.getPhoneType()));
	}

	if(hiddenBefore != lv_obj_has_flag(findPhone, LV_OBJ_FLAG_HIDDEN)){
		if(hiddenBefore && index >= 2){
			lv_obj_scroll_to_view(*items[index - 1], LV_ANIM_OFF);
		}else if(!hiddenBefore){
			if(index == 2){
				lv_obj_scroll_to_view(*items[0], LV_ANIM_OFF);
				lv_group_focus_obj(*items[0]);
			}else if(index > 2){
				lv_obj_scroll_to_view(*items[index - 1], LV_ANIM_OFF);
				lv_group_focus_obj(*items[index - 1]);
			}
		}
	}
}

void MainMenu::handleInput(Input::Data& event){
	if(event.btn == Input::Alt && event.action == Input::Data::Press){
		transition([](){ return std::make_unique<LockScreen>(); });
		lastIndex = 0;
	}
}

void MainMenu::startPhoneRing(){
	if(findPhoneRinging) return;

	findPhoneRinging = true;
	phone.findPhoneStart();
	findPhoneCounter = millis();
	findPhoneState = true;
}

void MainMenu::stopPhoneRing(){
	if(!findPhoneRinging) return;

	findPhoneRinging = false;
	phone.findPhoneStop();
}

void MainMenu::handleRing(){
	if(!findPhoneRinging) return;

	if(millis() - findPhoneCounter >= FindPhonePeriod){
		findPhoneCounter = millis();
		findPhoneState = !findPhoneState;
		findPhoneState ? phone.findPhoneStart() : phone.findPhoneStop();
	}
}

constexpr const char* MainMenu::getConnectionDesc(Phone::PhoneType type){
	if(type == Phone::PhoneType::None){
		return "Not connected\nto a smartphone.";
	}else if(type == Phone::PhoneType::Android){
		return "Connected to\nan Android device.";
	}else{
		return "Connected to\nan iPhone.";
	}
}
