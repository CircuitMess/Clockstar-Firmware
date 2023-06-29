#ifndef CLOCKSTAR_FIRMWARE_MAINMENU_H
#define CLOCKSTAR_FIRMWARE_MAINMENU_H

#include <map>
#include <memory>
#include "LV_Interface/LVScreen.h"
#include "UIElements/StatusBar.h"
#include "MenuItem.h"
#include "Notifs/Phone.h"

class MainMenu : public LVScreen {
public:
	MainMenu();

private:
	struct ItemInfo {
		const char* labelPath = nullptr;
		const char* iconPath = nullptr;
	};
	static constexpr ItemInfo ItemInfos[] = {
			{ "S:/menu/labels/connection.bin", "S:/menu/disconnected" },
			{ "S:/menu/labels/find.bin", "S:/menu/find" },
			{ "S:/menu/labels/level.bin", "S:/menu/level" },
			{ "S:/menu/labels/theremin.bin", "S:/menu/theremin" },
			{ "S:/menu/labels/settings.bin", "S:/menu/settings" },
	};
	static constexpr uint8_t ItemCount = sizeof(ItemInfos) / sizeof(ItemInfos[0]);

	static constexpr ItemInfo AltItems[] = {
			{ "S:/menu/labels/connection.bin", "S:/menu/connected" },
			{ "S:/menu/labels/ringing.bin", "S:/menu/ring" },
	};
	static constexpr uint8_t AltItemCount = sizeof(ItemInfos) / sizeof(ItemInfos[0]);

	Phone& phone;

	StatusBar* statusBar;

	lv_obj_t* bg;
	MenuItem* items[ItemCount];

	void onStarting() override;
	void loop() override;

	void onClick();

};


#endif //CLOCKSTAR_FIRMWARE_MAINMENU_H
