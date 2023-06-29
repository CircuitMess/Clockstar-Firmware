#include "MainMenu.h"
#include "Util/Services.h"
#include "MenuItemAlt.h"

MainMenu::MainMenu() : phone(*((Phone*) Services.get(Service::Phone))){
	lv_obj_set_size(*this, 128, LV_SIZE_CONTENT);
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	bg = lv_obj_create(*this);
	lv_obj_add_flag(bg, LV_OBJ_FLAG_FLOATING);
	lv_obj_set_size(bg, 128, 256);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", 0);

	for(int i = 0; i < ItemCount; i++){
		// TODO: connected/disconnected alt labels for phone connection
		// TODO: add "Press to stop" to ringing alt label
		if(i < AltItemCount){
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

	statusBar = new StatusBar(*this);
	lv_obj_add_flag(*this, LV_OBJ_FLAG_FLOATING);

	// Scrolling
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLL_ONE);
	lv_obj_set_scroll_snap_y(*this, LV_SCROLL_SNAP_START);
	lv_group_set_wrap(inputGroup, false);

	// TODO: hide "find phone" if disconnected or not connected to android phone
}

void MainMenu::onStarting(){
	lv_obj_scroll_to(*this, 0, 0, LV_ANIM_OFF);
	lv_group_focus_obj(*items[0]);
}

void MainMenu::loop(){
	statusBar->loop();
}

void MainMenu::onClick(){
	auto focused = lv_group_get_focused(inputGroup);
	auto index = lv_obj_get_index(focused);

	if(index < AltItemCount) return;

	// TODO: launch stuff
}
