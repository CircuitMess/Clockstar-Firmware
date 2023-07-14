#include "LabelElement.h"

#include <utility>
#include "Theme/theme.h"

LabelElement::LabelElement(lv_obj_t* parent, const char* name, std::function<void()> cb) : LVObject(parent), cb(std::move(cb)){
	lv_obj_add_flag(*this, LV_OBJ_FLAG_CLICKABLE);

	lv_style_set_border_width(defaultStyle, 1);
	lv_style_set_border_opa(defaultStyle, 0);
	lv_style_set_pad_all(defaultStyle, 3);
	lv_style_set_bg_opa(defaultStyle, 0);

	lv_style_set_border_width(focusedStyle, 1);
	lv_style_set_border_color(focusedStyle, lv_color_white());
	lv_style_set_border_opa(focusedStyle, LV_OPA_COVER);

	lv_style_set_text_font(labelStyle, &devin);
	lv_style_set_text_color(labelStyle, lv_color_white());

	lv_obj_set_height(*this, Height);
	lv_obj_set_width(*this, lv_pct(100));

	lv_obj_add_style(*this, focusedStyle, SelFocus);
	lv_obj_add_style(*this, defaultStyle, SelDefault);

	label = lv_label_create(*this);
	lv_obj_align(label, LV_ALIGN_LEFT_MID, 0, 0);
	lv_obj_add_style(label, labelStyle, 0);
	lv_label_set_text(label, name);

	lv_obj_add_event_cb(obj, [](lv_event_t* e){
		auto element = static_cast<LabelElement*>(e->user_data);
		if(element->cb) element->cb();
	}, LV_EVENT_CLICKED, this);

}
