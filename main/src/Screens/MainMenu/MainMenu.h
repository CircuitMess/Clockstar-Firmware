#ifndef CLOCKSTAR_FIRMWARE_MAINMENU_H
#define CLOCKSTAR_FIRMWARE_MAINMENU_H

#include <map>
#include <memory>
#include "LV_Interface/LVScreen.h"
#include "UIElements/StatusBar.h"
#include "MenuItem.h"
#include "Notifs/Phone.h"
#include "Devices/Input.h"

class MainMenu : public LVScreen {
public:
	MainMenu();
	virtual ~MainMenu();

private:
	struct ItemInfo {
		const char* labelPath = nullptr;
		const char* iconPath = nullptr;
	};
	static constexpr ItemInfo ItemInfos[] = {
			{ "S:/menu/labels/connection.bin", "S:/menu/disconnected" },
			{ "S:/menu/labels/find.bin",       "S:/menu/find" },
			{ "S:/menu/labels/level.bin",      "S:/menu/level" },
			{ "S:/menu/labels/theremin.bin",   "S:/menu/theremin" },
			{ "S:/menu/labels/settings.bin",   "S:/menu/settings" },
	};
	static constexpr uint8_t ItemCount = sizeof(ItemInfos) / sizeof(ItemInfos[0]);

	static constexpr ItemInfo AltItems[] = {
			{ "S:/menu/labels/connection.bin", "S:/menu/connected" },
			{ "S:/menu/labels/ringing.bin",    "S:/menu/ring" },
	};
	static constexpr uint8_t AltItemCount = sizeof(AltItems) / sizeof(AltItems[0]);

	bool findPhoneRinging = false;
	void startPhoneRing();
	void stopPhoneRing();
	void handleRing();

	bool findPhoneState = false;
	uint32_t findPhoneCounter = 0;
	static constexpr uint32_t FindPhonePeriod = 1000; //1 second

	Phone& phone;

	StatusBar* statusBar;

	lv_obj_t* bg;
	MenuItem* items[ItemCount];

	void onStarting() override;
	void onStop() override;
	void loop() override;
	EventQueue queue;

	void onClick();

	void handlePhoneChange(Phone::Event& event);
	void handleInput(Input::Data& event);
};


#endif //CLOCKSTAR_FIRMWARE_MAINMENU_H
