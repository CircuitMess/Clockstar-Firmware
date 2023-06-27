#ifndef CLOCKSTAR_FIRMWARE_ITEM_H
#define CLOCKSTAR_FIRMWARE_ITEM_H


#include "LV_Interface/LVStyle.h"
#include "LV_Interface/LVSelectable.h"
#include "Notifs/Notif.h"
#include "CtrlItem.h"

class Item : public LVSelectable {
public:
	Item(lv_obj_t* parent);

	void update(const Notif& notif);

private:
	LVStyle standard;
	LVStyle focused;

	lv_obj_t* top;
	lv_obj_t* icon;
	lv_obj_t* label;

	lv_obj_t* bot;
	lv_obj_t* body;

	lv_obj_t* ctrl;
	CtrlItem* del;
	CtrlItem* canc;

};


#endif //CLOCKSTAR_FIRMWARE_ITEM_H
