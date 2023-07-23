#ifndef CLOCKSTAR_FIRMWARE_SLEEPMAN_H
#define CLOCKSTAR_FIRMWARE_SLEEPMAN_H


#include "Sleep.h"
#include "Devices/IMU.h"
#include "Util/Events.h"
#include "LV_Interface/LVGL.h"
#include <memory>

class SleepMan {
public:
	SleepMan(LVGL& lvgl);
	void loop();

	void enAltLock(bool altLock);

private:
	LVGL& lvgl;
	Sleep sleep;
	EventQueue events;

	void handleInput(const Input::Data& evt);
	void handleMotion(const IMU::Event& evt);

	bool altLock = false;
	static constexpr uint32_t AltHoldTime = 300;
	uint32_t altPress;
	static constexpr uint32_t AltHoldCooldown = 100;
	uint32_t wakeTime = 0;

};


#endif //CLOCKSTAR_FIRMWARE_SLEEPMAN_H
