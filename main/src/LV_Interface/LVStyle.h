#ifndef CLOCKSTAR_FIRMWARE_LVSTYLE_H
#define CLOCKSTAR_FIRMWARE_LVSTYLE_H

#include <lvgl.h>


class LVStyle {
public:
	LVStyle();
	virtual ~LVStyle();

	operator lv_style_t*();

private:
	lv_style_t style{};
};


#endif //CLOCKSTAR_FIRMWARE_LVSTYLE_H
