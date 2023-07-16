#ifndef CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
#define CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H

#include "LV_Interface/LVScreen.h"
#include "Settings/Settings.h"
#include "Util/Events.h"
#include "UIElements/StatusBar.h"

class BoolElement;

class SliderElement;

class LabelElement;

class SettingsScreen : public LVScreen {
public:
	SettingsScreen();

private:
	void onStop() override;
	void loop() override;

	Settings& settings;

	lv_obj_t* bg;
	lv_obj_t* container;
	BoolElement* audio;
	SliderElement* brightness;
	StatusBar* statusBar;
	LabelElement* saveAndExit;

};


#endif //CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
