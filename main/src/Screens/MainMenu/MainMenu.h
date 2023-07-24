#ifndef CLOCKSTAR_FIRMWARE_MAINMENU_H
#define CLOCKSTAR_FIRMWARE_MAINMENU_H

#include <map>
#include <memory>
#include "LV_Interface/LVScreen.h"
#include "UIElements/StatusBar.h"
#include "MenuItem.h"
#include "Notifs/Phone.h"
#include "Devices/Input.h"
#include "MenuItemAlt.h"

class MainMenu : public LVScreen {
public:
	MainMenu();
	virtual ~MainMenu();

private:
	static constexpr const char* ConnDesc[3] = {
			"Not connected.\nUse phone to pair",
			"Connected to\nAndroid device",
			"Connected to\niOS device"
	};

	struct ItemInfo {
		const char* labelPath = nullptr;
		const char* labelAlt = nullptr;
		const char* iconPath = nullptr;
		const char* iconAltPath = nullptr;
	};
	static constexpr ItemInfo ItemInfos[] = {
			{ "S:/menu/labels/find.bin",       "S:/menu/labels/ringing.bin",              "S:/menu/find",         "S:/menu/ring" },
			{ "S:/menu/labels/level.bin",      nullptr,                                "S:/menu/level",        nullptr },
			{ "S:/menu/labels/theremin.bin",   nullptr,                                "S:/menu/theremin",     nullptr },
			{ "S:/menu/labels/connection.bin", ConnDesc[(int) Phone::PhoneType::None], "S:/menu/disconnected", "S:/menu/connected" },
			{ "S:/menu/labels/settings.bin",   nullptr,                                "S:/menu/settings",     nullptr },
	};
	static constexpr uint8_t ItemCount = sizeof(ItemInfos) / sizeof(ItemInfos[0]);

	void setConnAlts();

	bool findPhoneRinging = false;
	void startPhoneRing();
	void stopPhoneRing();
	void handleRing();

	bool findPhoneState = false;
	uint32_t findPhoneCounter = 0;
	static constexpr uint32_t FindPhonePeriod = 1000; //1 second

	static uint8_t lastIndex;

	Phone& phone;

	StatusBar* statusBar;

	lv_obj_t* bg;
	MenuItem* items[ItemCount];
	// MenuItemAlt* phoneConnection;

	void onStarting() override;
	void onStop() override;
	void loop() override;
	EventQueue queue;

	void onClick();

	void handlePhoneChange(Phone::Event& event);
	void handleInput(Input::Data& event);
};


#endif //CLOCKSTAR_FIRMWARE_MAINMENU_H
