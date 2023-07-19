#ifndef CLOCKSTAR_FIRMWARE_CTRLITEM_H
#define CLOCKSTAR_FIRMWARE_CTRLITEM_H

#include "LV_Interface/LVObject.h"

class CtrlItem : public LVObject {
public:
	CtrlItem(lv_obj_t* parent, const char* desel, const char* sel);
	virtual ~CtrlItem();

private:
	const char* desel;
	const char* sel;
	lv_obj_t* icon;

	static void cbFocus(lv_event_t* evt);
	static void cbDefocus(lv_event_t* evt);

};


#endif //CLOCKSTAR_FIRMWARE_CTRLITEM_H
