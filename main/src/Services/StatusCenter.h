#ifndef CLOCKSTAR_FIRMWARE_STATUSCENTER_H
#define CLOCKSTAR_FIRMWARE_STATUSCENTER_H


#include "Util/Threaded.h"
#include "Util/Events.h"
#include "Notifs/Phone.h"
#include "Devices/Battery.h"
#include "ChirpSystem.h"
#include "Settings/Settings.h"
#include "Devices/LEDController.h"

class StatusCenter : public Threaded {
public:
	StatusCenter();

	void blockAudio(bool block);

	void updateLED();
	void blink();
	void beep();

private:
	EventQueue events;

	ChirpSystem& chirp;
	Settings& settings;
	Phone& phone;
	RGBLEDController* led;

	bool audioBlocked = false;
	bool hasNotifs = false;
	enum { Ok, Empty, Charging } battState = Ok;

	void loop() override;

	void processPhone(const Phone::Event& evt);
	void processBatt(const Battery::Event& evt);

};


#endif //CLOCKSTAR_FIRMWARE_STATUSCENTER_H
