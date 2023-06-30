#include "MenuItem.h"
#include "UIElements/StatusBar.h"

MenuItem::MenuItem(lv_obj_t* parent, const char* gifPath, const char* labelPath) : LVObject(parent){
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	lv_obj_set_size(*this, 128, 128);
	lv_obj_set_style_pad_gap(*this, 4, 0);
	lv_obj_set_style_pad_top(*this, 16, 0);

	labelContainer = lv_obj_create(*this);
	lv_obj_set_size(labelContainer, lv_pct(100), 26);
	lv_obj_set_flex_flow(labelContainer, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(labelContainer, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_gap(labelContainer, 2, 0);

	label = lv_img_create(labelContainer);

	constructVis(gifPath, labelPath);

	lv_obj_add_event_cb(*this, [](lv_event_t* e){
		auto item = static_cast<MenuItem*>(e->user_data);
		item->onFocus();
	}, LV_EVENT_FOCUSED, this);

	lv_obj_add_event_cb(*this, [](lv_event_t* e){
		auto item = static_cast<MenuItem*>(e->user_data);
		item->onDefocus();
	}, LV_EVENT_DEFOCUSED, this);
}

void MenuItem::constructVis(const char* gifPath, const char* labelPath){
	lv_img_set_src(label, labelPath);

	if(gif != nullptr){
		lv_obj_del(*gif);
	}

	gif = new LVGIF(*this, gifPath);
	gif->setLooping(LVGIF::LoopType::On);
	gif->reset();
	gif->stop();

	lv_obj_move_to_index(*gif, 0);
}

void MenuItem::onFocus(){
	gif->reset();
	gif->start();
}

void MenuItem::onDefocus(){
	gif->stop();
}
