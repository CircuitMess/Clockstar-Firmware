#include "MenuItemAlt.h"

MenuItemAlt::MenuItemAlt(lv_obj_t* parent, const char* gifPath, const char* labelPath)
		: MenuItem(parent, gifPath, labelPath), gifPath(gifPath), labelPath(labelPath){

	lv_obj_add_event_cb(*this, [](lv_event_t* e){
		auto item = static_cast<MenuItemAlt*>(e->user_data);
		item->onClick();
	}, LV_EVENT_CLICKED, this);
}

void MenuItemAlt::setAltPaths(const char* gifPathAlt, const char* labelPathAlt){
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
	constructVis(gifPath.c_str(), labelPath.c_str());
	isAlt = false;
}

void MenuItemAlt::setAlt(){
	constructVis(gifPathAlt.c_str(), labelPathAlt.c_str());
	isAlt = true;
}
