#ifndef CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
#define CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H

#include "LV_Interface/LVScreen.h"
#include "Settings/Settings.h"
#include "Util/Events.h"
#include "UIElements/StatusBar.h"
#include "Services/BacklightBrightness.h"
#include "Services/ChirpSystem.h"

class BoolElement;

class SliderElement;

class LabelElement;

class DiscreteSliderElement;

class SettingsScreen : public LVScreen {
public:
	SettingsScreen();

private:
	void onStarting() override;
	void onStop() override;
	void loop() override;

	Settings& settings;
	BacklightBrightness& backlight;
	ChirpSystem& audio;

	lv_obj_t* bg;
	lv_obj_t* container;
	BoolElement* audioSwitch;
	SliderElement* brightnessSlider;
	BoolElement* ledSwitch;
	StatusBar* statusBar;
	DiscreteSliderElement* sleepSlider;
	LabelElement* saveAndExit;

};


#endif //CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
