#include "MenuItemAlt.h"

MenuItemAlt::MenuItemAlt(lv_obj_t* parent, const char* gifPath, const char* labelPath)
		: MenuItem(parent, gifPath, labelPath), gifPath(gifPath), labelPath(labelPath){

	lv_obj_add_event_cb(*this, [](lv_event_t* e){
		auto item = static_cast<MenuItemAlt*>(e->user_data);
		item->onClick();
	}, LV_EVENT_CLICKED, this);

	textLabel = lv_label_create(labelContainer);
	lv_obj_add_flag(textLabel, LV_OBJ_FLAG_HIDDEN);
	lv_label_set_long_mode(textLabel, LV_LABEL_LONG_WRAP);
	lv_obj_set_width(textLabel, lv_pct(100));
	lv_obj_set_style_text_align(textLabel, LV_TEXT_ALIGN_CENTER, 0);
}

void MenuItemAlt::setAltPaths(const char* gifPathAlt, const char* labelPathAlt){
	lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
	lv_obj_add_flag(textLabel, LV_OBJ_FLAG_HIDDEN);

	this->gifPathAlt = gifPathAlt;
	this->labelPathAlt = labelPathAlt;

	if(isAlt){
		setAlt();
		MenuItem::onFocus();
	}
}

void MenuItemAlt::onClick(){
	if(isAlt){
		setOrig();
	}else{
		setAlt();
	}

	MenuItem::onFocus();
}

void MenuItemAlt::onDefocus(){
	if(isAlt){
		setOrig();
	}

	MenuItem::onDefocus();
}

void MenuItemAlt::setOrig(){
		if(!labelTextAlt.empty()){

		lv_obj_add_flag(textLabel, LV_OBJ_FLAG_HIDDEN);
		lv_obj_clear_flag(label, LV_OBJ_FLAG_HIDDEN);
	}
	constructVis(gifPath.c_str(), labelPath.c_str());
	isAlt = false;
}

void MenuItemAlt::setAlt(){
	if(!labelTextAlt.empty()){

		lv_obj_clear_flag(textLabel, LV_OBJ_FLAG_HIDDEN);
		lv_obj_add_flag(label, LV_OBJ_FLAG_HIDDEN);
	}

	constructVis(gifPathAlt.c_str(), labelPathAlt.c_str());
	lv_label_set_text(textLabel, labelTextAlt.c_str());
	isAlt = true;
}

void MenuItemAlt::setAltLabel(const char* gifPathAlt, const char* labelTextAlt){
	this->gifPathAlt = gifPathAlt;
	this->labelTextAlt = labelTextAlt;

	if(isAlt){
		setAlt();
		MenuItem::onFocus();
	}

}
