#ifndef CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
#define CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H

#include "LV_Interface/LVScreen.h"
#include "Settings/Settings.h"
#include "Util/Events.h"
#include "UIElements/StatusBar.h"

class BoolElement;

class SliderElement;

class SettingsScreen : public LVScreen {
public:
	SettingsScreen();

private:
	void onStop() override;
	void loop() override;

	Settings& settings;
	EventQueue queue;

	lv_obj_t* bg;
	lv_obj_t* container;
	BoolElement* audio;
	SliderElement* brightness;
	StatusBar* statusBar;

};


#endif //CLOCKSTAR_FIRMWARE_SETTINGSSCREEN_H
