#ifndef CLOCKSTAR_FIRMWARE_STATUSBAR_H
#define CLOCKSTAR_FIRMWARE_STATUSBAR_H


#include "LV_Interface/LVObject.h"
#include "ClockLabel.h"
#include "Services/Time.h"
#include "Notifs/Phone.h"
#include "Util/Events.h"
#include "Devices/Battery.h"
#include "BatteryElement.h"

class StatusBar : public LVObject {
public:
	explicit StatusBar(lv_obj_t* parent, bool showClock = true);
	void loop();

private:
	Phone& phone;
	Battery& battery;

	EventQueue queue;

	bool connected = false;

	lv_obj_t* left;
	BatteryElement* batPhone;
	lv_obj_t* phoneIcon;
	ClockLabel* clock = nullptr;
	BatteryElement* batDevice;

	void setPhoneConnected();
	void setPhoneBattery();
	void setDeviceBattery();

	static BatteryElement::Level getLevel(uint8_t level);
};


#endif //CLOCKSTAR_FIRMWARE_STATUSBAR_H
