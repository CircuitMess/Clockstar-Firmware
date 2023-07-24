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
	void enAutoSleep(bool autoSleep);

private:
friend IMU;

	Sleep sleep;
	EventQueue events;

	LVGL& lvgl;
	IMU& imu;

	void goSleep();

	uint32_t actTime = 0;
	bool autoSleep = true;
	void checkAutoSleep();

	void checkEvents();
	void handleInput(const Input::Data& evt);
	void handleMotion(const IMU::Event& evt);

	static constexpr uint32_t WakeCooldown = 100;
	uint32_t wakeTime = 0;

	bool altLock = false;
	static constexpr uint32_t AltHoldTime = 300;
	uint32_t altPress;

};


#endif //CLOCKSTAR_FIRMWARE_SLEEPMAN_H
