#include <regex>
#include "Item.h"

Item::Item(lv_obj_t* parent, std::function<void()> dismiss) : LVSelectable(parent), onDismiss(dismiss){
	lv_obj_set_size(*this, lv_pct(100), LV_SIZE_CONTENT);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);

	lv_obj_add_flag(*this, LV_OBJ_FLAG_CLICKABLE);

	lv_obj_add_style(*this, standard, LV_STATE_DEFAULT);
	lv_obj_add_style(*this, focused, LV_STATE_FOCUSED);

	lv_style_set_radius(standard, 3);
	lv_style_set_pad_top(standard, 2);
	lv_style_set_pad_bottom(standard, 3);
	lv_style_set_pad_hor(standard, 3);
	lv_style_set_pad_gap(standard, 4);

	lv_style_set_border_width(standard, 1);
	lv_style_set_border_color(standard, lv_color_white());
	lv_style_set_border_opa(standard, 40);

	lv_style_set_bg_color(focused, lv_color_white());
	lv_style_set_bg_opa(focused, 40);
	lv_style_set_border_opa(focused, LV_OPA_0);

	top = lv_obj_create(*this);
	lv_obj_set_size(top, lv_pct(100), 11);
	lv_obj_set_flex_flow(top, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(top, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	auto iconCont = lv_obj_create(top);
	lv_obj_set_size(iconCont, 13, 11); // maybe
	lv_obj_set_flex_flow(iconCont, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(iconCont, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_END, LV_FLEX_ALIGN_END);
	icon = lv_img_create(iconCont);

	label = lv_label_create(top);
	lv_obj_set_style_pad_left(label, 4, 0);
	lv_label_set_long_mode(label, LV_LABEL_LONG_CLIP);
	lv_obj_set_style_text_color(label, lv_color_make(244, 126, 27), 0);

	bot = lv_obj_create(*this);
	lv_obj_set_size(bot, lv_pct(100), LV_SIZE_CONTENT);

	body = lv_label_create(bot);
	lv_obj_set_size(body, lv_pct(100), 8);
	lv_obj_set_style_max_height(body, 34, 0);
	lv_obj_set_style_pad_hor(body, 2, 0);

	lv_label_set_long_mode(body, LV_LABEL_LONG_DOT);

	lv_obj_add_event_cb(*this, [](lv_event_t* evt){
		auto item = static_cast<Item*>(evt->user_data);
		lv_label_set_long_mode(item->body, LV_LABEL_LONG_SCROLL);
		lv_obj_set_size(item->body, lv_pct(100), LV_SIZE_CONTENT);
		lv_obj_clear_flag(item->ctrl, LV_OBJ_FLAG_HIDDEN);
		lv_group_focus_obj(*item->canc);
		lv_obj_scroll_to_view(*item, LV_ANIM_ON);
	}, LV_EVENT_CLICKED, this);

	lv_obj_add_event_cb(*this, [](lv_event_t* evt){
		auto item = static_cast<Item*>(evt->user_data);
		lv_label_set_long_mode(item->body, LV_LABEL_LONG_DOT);
		lv_obj_set_size(item->body, lv_pct(100), 8);
		lv_obj_add_flag(item->ctrl, LV_OBJ_FLAG_HIDDEN);
	}, LV_EVENT_READY, this);

	ctrl = lv_obj_create(*this);
	lv_obj_set_size(ctrl, lv_pct(100), LV_SIZE_CONTENT);
	lv_obj_set_style_bg_color(ctrl, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(ctrl, LV_OPA_30, 0);
	lv_obj_get_style_flex_flow(ctrl, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(ctrl, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_radius(ctrl, 3, 0);

	del = new CtrlItem(ctrl, "S:/icon/trash.bin", "S:/icon/trash_sel.bin");
	canc = new CtrlItem(ctrl, "S:/icon/x.bin", "S:/icon/x_sel.bin");

	lv_obj_add_event_cb(*canc, [](lv_event_t* evt){
		auto item = static_cast<Item*>(evt->user_data);
		item->deselect();
	}, LV_EVENT_CLICKED, this);

	lv_obj_add_event_cb(*del, [](lv_event_t* evt){
		auto item = static_cast<Item*>(evt->user_data);
		item->deselect();

		auto dismiss = item->onDismiss;
		dismiss();
	}, LV_EVENT_CLICKED, this);

	lv_group_add_obj(inputGroup, *del);
	lv_group_add_obj(inputGroup, *canc);
	lv_group_set_wrap(inputGroup, false);

	lv_obj_add_flag(ctrl, LV_OBJ_FLAG_HIDDEN);

}

void Item::update(const Notif& notif){
	lv_img_set_src(icon, iconPath(notif));

	lv_label_set_text(label, notif.title.c_str());

	// TODO: replace line breaks (two characters: \ and n when coming from Bangle, needs checking from ANCS) with two space characters
	// if ANCS has proper line breaks, adjust Bangle so it has proper line breaks too
	auto copy = notif.message;
	copy = std::regex_replace(copy, std::regex("\\\n"), "  ");

	lv_label_set_text(body, copy.c_str());
}
