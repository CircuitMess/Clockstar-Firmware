#ifndef CLOCKSTAR_FIRMWARE_MENUITEM_H
#define CLOCKSTAR_FIRMWARE_MENUITEM_H

#include "LV_Interface/LVObject.h"
#include "LV_Interface/LVGIF.h"

class MenuItem : public LVObject {
public:
	MenuItem(lv_obj_t* parent, const char* gifPath, const char* labelPath);

protected:
	LVGIF* gif = nullptr;
	lv_obj_t* labelContainer;
	lv_obj_t* label = nullptr;

	void constructVis(const char* gifPath, const char* labelPath);

	virtual void onFocus();
	virtual void onDefocus();

};


#endif //CLOCKSTAR_FIRMWARE_MENUITEM_H
