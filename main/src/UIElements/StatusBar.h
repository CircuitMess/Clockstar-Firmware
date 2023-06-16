#ifndef CLOCKSTAR_FIRMWARE_STATUSBAR_H
#define CLOCKSTAR_FIRMWARE_STATUSBAR_H


#include "LV_Interface/LVObject.h"
#include "LV_Interface/LVStyle.h"

class StatusBar : public LVObject {
public:
	explicit StatusBar(lv_obj_t* parent);

	void hideClock();
	void setTime(uint8_t h, uint8_t m);
	void setConnection(bool connected);
	void setDeviceBattery(uint8_t percent);
	void setPhoneBattery(uint8_t percent);

private:
	bool connection = false;

	static constexpr uint8_t Width = 128;
	static constexpr uint8_t Height = 15;

	lv_obj_t* timeLabel;
	lv_obj_t* deviceBat, * phoneBat, * phoneStatus;
	lv_obj_t* phoneContainer;

	static constexpr uint8_t PhoneContainerWidth = 25;
	static constexpr uint8_t PhoneContainerHeight = 13;

	LVStyle textStyle;
	const lv_color_t textColor = lv_color_make(207, 198, 184);
	static const char* percentToIcon(uint8_t percent);
};


#endif //CLOCKSTAR_FIRMWARE_STATUSBAR_H
