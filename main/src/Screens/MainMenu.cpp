#include <string>
#include "MainMenu.h"
#include "Level.h"
#include "Theme/theme.h"

//TODO - fill launchMap with other screens
const std::map<uint8_t, LVScreen* (*)()> MainMenu::launchMap = {
		{ 2, []() -> LVScreen*{ return new Level(); }},
		{ 3, []() -> LVScreen*{ return new Level(); }},
		{ 4, []() -> LVScreen*{ return new Level(); }}
};


MainMenu::MainMenu() : statusBar(*this){

	lv_style_set_text_color(textStyle, TextColor);

	lv_style_set_text_color(subtextStyle, SubtextColor);
	lv_style_set_text_align(subtextStyle, LV_TEXT_ALIGN_CENTER);
	lv_style_set_text_font(subtextStyle, &devin);
	lv_style_set_text_line_space(subtextStyle, 2);

	lv_style_set_border_width(debugStyle, 1);
	lv_style_set_border_opa(debugStyle, LV_OPA_COVER);
	lv_style_set_border_color(debugStyle, lv_palette_main(LV_PALETTE_GREEN));


	bg = lv_obj_create(*this);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_size(bg, 128, 128);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", LV_STATE_DEFAULT);
	lv_obj_set_style_bg_img_tiled(bg, true, 0);

	lv_obj_move_foreground(statusBar);


	lv_obj_set_flex_flow(bg, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(bg, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_START);
	lv_obj_set_style_pad_gap(bg, 10, 0);

	for(int i = 0; i < ItemCount; i++){
		auto& container = itemContainers[i].container;
		auto& labelContainer = itemContainers[i].labelContainer;
		container = lv_obj_create(bg);
		lv_obj_set_size(container, lv_pct(100), lv_pct(100));

		if(i == 0){
			//Phone connection
			connectedGif = new LVGIF(container, ConnectedGifPath);
			connectedGif->start();
			connectedGif->stop();
			connectedGif->setLooping(LVGIF::LoopType::Single);
			lv_obj_add_flag(*connectedGif, LV_OBJ_FLAG_HIDDEN);
		}else if(i == 1){
			//Find phone
			ringingGif = new LVGIF(container, RingingGifPath);
			ringingGif->start();
			ringingGif->stop();
			ringingGif->setLooping(LVGIF::LoopType::On);
			lv_obj_add_flag(*ringingGif, LV_OBJ_FLAG_HIDDEN);
		}

		auto gif = new LVGIF(container, Items[i].icon);
		itemContainers[i].gif = gif;
		gif->start();
		gif->stop();
		gif->setLooping(LVGIF::LoopType::On);

		labelContainer = lv_obj_create(container);
		lv_obj_set_size(labelContainer, lv_pct(100), lv_pct(20));
		lv_obj_set_flex_flow(labelContainer, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(labelContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_set_style_pad_gap(labelContainer, 2, 0);
		itemContainers[i].label = lv_img_create(labelContainer);
		lv_img_set_src(itemContainers[i].label, Items[i].label);
		lv_obj_center(itemContainers[i].label);


		lv_obj_set_flex_flow(container, LV_FLEX_FLOW_COLUMN);
		lv_obj_set_flex_align(container, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
		lv_obj_set_style_pad_gap(container, 4, 0);
		lv_obj_set_style_pad_top(container, 10, 0);
		lv_obj_set_width(container, lv_pct(100));
		lv_obj_set_height(container, lv_pct(100));

		lv_obj_clear_flag(container, LV_OBJ_FLAG_SCROLLABLE);
		lv_obj_add_flag(container, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_group_add_obj(inputGroup, container);

		lv_obj_add_event_cb(container, [](lv_event_t* e){
			auto selected = lv_obj_get_index(lv_event_get_target(e));
			auto menu = (MainMenu*) e->user_data;
			menu->launch(selected);
		}, LV_EVENT_CLICKED, this);

		lv_obj_add_event_cb(container, [](lv_event_t* e){
			auto gif = (LVGIF*) e->user_data;
			gif->reset();
		}, LV_EVENT_FOCUSED, gif);

		lv_obj_add_event_cb(container, [](lv_event_t* e){
			auto selected = lv_obj_get_index(lv_event_get_target(e));
			auto menu = (MainMenu*) e->user_data;
			auto gif = menu->itemContainers[selected].gif;

			gif->stop();
			menu->resetAction(selected);
		}, LV_EVENT_DEFOCUSED, this);


//		lv_obj_add_style(labelContainer, debugStyle, 0);

	}


	lv_group_set_wrap(inputGroup, false);
	lv_group_focus_obj(itemContainers[0].container);

	if(/*not connected to android phone*/ false){
		lv_obj_add_flag(itemContainers[1].container, LV_OBJ_FLAG_HIDDEN);
	}
}

void MainMenu::loop(){
	/*
	 * TODO - get time, connection, battery info and forward to statusBar
	 * wait for connection event (nonblocking) and if android connection is present hide/unhide ringing phone container
	 * if connected and if currently in phoneConnection change gif and text
	 * if disconnected and in phoneConnection or findPhone call resetAction(selectedIndex) and hide ringing container
	 */

}

void MainMenu::onStart(){
	//TODO - get initial time, connection, battery info and forward to statusBar
}

void MainMenu::launch(uint8_t index){
	if(index == 0){
		//Phone connection
		auto label = itemContainers[index].label;
		lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
		if(/*connected*/ true){
			if(lv_obj_get_child_cnt(itemContainers[index].labelContainer) <= 1){
				auto statusLabel = lv_label_create(itemContainers[index].labelContainer);
				//TODO - print text with connected phone info
				lv_label_set_text(statusLabel, "Connected to\nLea's phone");
				lv_obj_add_style(statusLabel, subtextStyle, 0);
				lv_obj_center(statusLabel);

				lv_obj_add_flag(*itemContainers[index].gif, LV_OBJ_FLAG_HIDDEN);
				lv_obj_clear_flag(*connectedGif, LV_OBJ_FLAG_HIDDEN);
				connectedGif->reset();
				connectedGif->start();
				itemContainers[index].gif->stop();
			}
		}else{
			if(lv_obj_get_child_cnt(itemContainers[index].labelContainer) <= 1){
				auto statusLabel = lv_label_create(itemContainers[index].labelContainer);
				lv_label_set_text(statusLabel, "Not paired.\nAccepting connections");
				lv_obj_add_style(statusLabel, subtextStyle, 0);
				lv_obj_center(statusLabel);
			}
		}
	}else if(index == 1){
		//Find my phone
		if(lv_obj_get_child_cnt(itemContainers[index].labelContainer) <= 1){
			lv_img_set_src(itemContainers[index].label, RingLabelPath);

			auto statusLabel = lv_label_create(itemContainers[index].labelContainer);
			lv_label_set_text(statusLabel, "press to cancel");
			lv_obj_add_style(statusLabel, subtextStyle, 0);
			lv_obj_align(statusLabel, LV_ALIGN_BOTTOM_MID, 0, 0);

			lv_obj_add_flag(*itemContainers[index].gif, LV_OBJ_FLAG_HIDDEN);
			lv_obj_clear_flag(*ringingGif, LV_OBJ_FLAG_HIDDEN);
			ringingGif->reset();
			ringingGif->start();
			itemContainers[index].gif->stop();
		}else{
			resetAction(index);
		}
	}else{
		LVScreen* screen = launchMap.at(index)();
		if(screen){
			push(screen);
		}
	}
}

void MainMenu::resetAction(uint8_t index){
	if(index == 0){
		//Phone connection
		auto label = itemContainers[index].label;
		lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(*itemContainers[index].gif, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(*connectedGif, LV_OBJ_FLAG_HIDDEN);

		if(lv_obj_get_child_cnt(itemContainers[index].labelContainer) > 1){
			lv_obj_del(lv_obj_get_child(itemContainers[index].labelContainer, -1));
		}
	}else if(index == 1){
		//Find my phone
		auto label = itemContainers[index].label;
		lv_img_set_src(label, Items[index].label);
		lv_obj_clear_flag(*itemContainers[index].gif, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(*ringingGif, LV_OBJ_FLAG_HIDDEN);
		itemContainers[index].gif->reset();


		if(lv_obj_get_child_cnt(itemContainers[index].labelContainer) > 1){
			lv_obj_del(lv_obj_get_child(itemContainers[index].labelContainer, -1));
		}
	}
}

MainMenu::~MainMenu(){
	for(auto& item: itemContainers){
		delete item.gif;
	}
	delete ringingGif;
	delete connectedGif;
}
