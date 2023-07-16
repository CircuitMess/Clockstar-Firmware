#ifndef CLOCKSTAR_FIRMWARE_LABELELEMENT_H
#define CLOCKSTAR_FIRMWARE_LABELELEMENT_H

#include <functional>
#include "LV_Interface/LVObject.h"
#include "LV_Interface/LVStyle.h"

class LabelElement : public LVObject {
public:
	explicit LabelElement(lv_obj_t* parent, const char* name, std::function<void()> cb);

private:
	lv_obj_t* label;

	LVStyle defaultStyle;
	LVStyle focusedStyle;
	LVStyle labelStyle;
	static constexpr lv_style_selector_t SelDefault = LV_PART_MAIN | LV_STATE_DEFAULT;
	static constexpr lv_style_selector_t SelFocus = LV_PART_MAIN | LV_STATE_FOCUSED;

	std::function<void()> cb;
	static constexpr uint8_t Height = 23;

};


#endif //CLOCKSTAR_FIRMWARE_LABELELEMENT_H
