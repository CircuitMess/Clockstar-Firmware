#ifndef CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
#define CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H

#include "LV_Interface/LVScreen.h"
#include "Settings/Settings.h"
#include "Util/Events.h"
#include "UIElements/StatusBar.h"
#include "Services/BacklightBrightness.h"
#include "Services/ChirpSystem.h"
#include "Devices/IMU.h"

class BoolElement;

class SliderElement;

class LabelElement;

class DiscreteSliderElement;

class LVModal;

class SettingsScreen : public LVScreen {
public:
	SettingsScreen();

private:
	void onStarting() override;
	void onStart() override;
	void onStop() override;
	void loop() override;

	Settings& settings;
	BacklightBrightness& backlight;
	ChirpSystem& audio;
	IMU& imu;
	Time& ts;

	lv_obj_t* bg;
	lv_obj_t* container;
	LabelElement* manualTime;
	BoolElement* audioSwitch;
	SliderElement* brightnessSlider;
	BoolElement* ledSwitch;
	StatusBar* statusBar;
	DiscreteSliderElement* sleepSlider;
	LabelElement* saveAndExit;
	BoolElement* motionSwitch;
	BoolElement* rotationSwitch;

	LVModal* timePickerModal;

	static constexpr uint8_t TopPadding = 18;

	EventQueue queue;

};


#endif //CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
