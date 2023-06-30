#ifndef CLOCKSTAR_FIRMWARE_CTRLITEM_H
#define CLOCKSTAR_FIRMWARE_CTRLITEM_H

#include "LV_Interface/LVObject.h"

class CtrlItem : public LVObject {
public:
	CtrlItem(lv_obj_t* parent, const char* desel, const char* sel);

private:
	const char* desel;
	const char* sel;
	lv_obj_t* icon;

};


#endif //CLOCKSTAR_FIRMWARE_CTRLITEM_H
