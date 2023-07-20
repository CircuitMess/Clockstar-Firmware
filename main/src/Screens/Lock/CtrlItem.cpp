#include "CtrlItem.h"

CtrlItem::CtrlItem(lv_obj_t* parent, const char* desel, const char* sel) : LVObject(parent), desel(desel), sel(sel){
	lv_obj_set_flex_align(*this, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_size(*this, lv_pct(50), LV_SIZE_CONTENT);
	lv_obj_set_style_radius(*this, 3, 0);
	lv_obj_set_style_pad_ver(*this, 4, 0);

	lv_obj_set_style_bg_color(*this, lv_color_white(), 0);
	lv_obj_set_style_bg_opa(*this, LV_OPA_0, 0);
	lv_obj_set_style_bg_opa(*this, LV_OPA_20, LV_STATE_FOCUSED);

	icon = lv_img_create(*this);
	lv_obj_set_size(icon, 10, 10);
	lv_img_set_src(icon, desel);

	lv_obj_add_event_cb(*this, cbFocus, LV_EVENT_FOCUSED, this);
	lv_obj_add_event_cb(*this, cbDefocus, LV_EVENT_DEFOCUSED, this);
}

CtrlItem::~CtrlItem(){
	lv_obj_remove_event_cb(*this, cbFocus);
	lv_obj_remove_event_cb(*this, cbDefocus);
}

void CtrlItem::cbFocus(lv_event_t* evt){
	auto item = static_cast<CtrlItem*>(evt->user_data);
	lv_img_set_src(item->icon, item->sel);
}

void CtrlItem::cbDefocus(lv_event_t* evt){
	auto item = static_cast<CtrlItem*>(evt->user_data);
	lv_img_set_src(item->icon, item->desel);
}
