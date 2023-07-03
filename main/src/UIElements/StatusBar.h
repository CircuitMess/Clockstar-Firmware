#ifndef CLOCKSTAR_FIRMWARE_STATUSBAR_H
#define CLOCKSTAR_FIRMWARE_STATUSBAR_H


#include "LV_Interface/LVObject.h"
#include "ClockLabel.h"
#include "Services/Time.h"
#include "Notifs/Phone.h"
#include "Util/Events.h"
#include "Devices/Battery.h"

class StatusBar : public LVObject {
public:
	explicit StatusBar(lv_obj_t* parent, bool showClock = true);

	void loop();

private:
	Phone& phone;
	Battery& battery;

	EventQueue queue;

	bool connected = false;
	uint8_t perBatPhone = 0;
	uint8_t perBatDevice = 0;

	lv_obj_t* left;
	lv_obj_t* right;
	lv_obj_t* batPhone;
	lv_obj_t* phoneIcon;
	ClockLabel* clock = nullptr;
	lv_obj_t* batDevice;

	void setPhoneConnected();
	void setPhoneBattery();
	void setDeviceBattery();

	bool chargingAnimation = false;
	uint8_t chargingIndex = 0;
	static constexpr uint32_t ChargingAnimTime = 500;
	static constexpr uint8_t BatteryLevels = 3;
	static constexpr const char* BatteryIcons[] = { "S:/icons/batteryLow.bin", "S:/icons/batteryMid.bin", "S:/icons/batteryFull.bin" };
	uint32_t chargingMillis = 0;

	bool lowBatteryAnimation = false;
	static constexpr uint32_t LowBatteryAnimTime = 500;
	bool lowBatteryAnimToggle = false;
	uint32_t lowBatMillis = 0;

	void chargingEvent(bool chargeStatus);
	void lowBatteryEvent();


	static const char* percentToIcon(uint8_t percent);
};


#endif //CLOCKSTAR_FIRMWARE_STATUSBAR_H
