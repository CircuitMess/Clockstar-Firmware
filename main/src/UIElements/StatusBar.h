#ifndef CLOCKSTAR_FIRMWARE_STATUSBAR_H
#define CLOCKSTAR_FIRMWARE_STATUSBAR_H


#include "LV_Interface/LVObject.h"
#include "ClockLabelSmall.h"
#include "Services/Time.h"
#include "Notifs/Phone.h"
#include "Util/Events.h"

class StatusBar : public LVObject {
public:
	explicit StatusBar(lv_obj_t* parent, bool showClock = true);

	void loop();

private:
	Phone& phone;

	EventQueue queue;

	bool connected = false;
	uint8_t perBatPhone = 0;
	uint8_t perBatDevice = 0;

	lv_obj_t* left;
	lv_obj_t* batPhone;
	lv_obj_t* phoneIcon;
	ClockLabelSmall* clock = nullptr;
	lv_obj_t* batDevice;

	void setPhoneConnected();
	void setPhoneBattery();
	void setDeviceBattery();

	static const char* percentToIcon(uint8_t percent);
};


#endif //CLOCKSTAR_FIRMWARE_STATUSBAR_H
