#ifndef CLOCKSTAR_FIRMWARE_MAINMENU_H
#define CLOCKSTAR_FIRMWARE_MAINMENU_H

#include <map>
#include "../LV_Interface/LVScreen.h"
#include "../LV_Interface/LVStyle.h"
#include "../UIElements/StatusBar.h"
#include "../LV_Interface/LVGIF.h"

class MainMenu : public LVScreen {
public:
	MainMenu();
	~MainMenu() override;
	void onStart() override;

private:
	void loop() override;

	void launch(uint8_t index);
	void resetAction(uint8_t index);

	lv_obj_t* bg;
	StatusBar statusBar;

	struct Item {
		const char* label;
		const char* icon;
	} static constexpr Items[] = {
			{ "S:/mainMenu/labels/connection.bin", "S:/mainMenu/disconnected" },
			{ "S:/mainMenu/labels/find.bin",       "S:/mainMenu/find" },
			{ "S:/mainMenu/labels/level.bin",      "S:/mainMenu/level" },
			{ "S:/mainMenu/labels/theremin.bin",   "S:/mainMenu/theremin" },
			{ "S:/mainMenu/labels/settings.bin",   "S:/mainMenu/settings" }};

	static const std::map<uint8_t, LVScreen* (*)()> launchMap;

	static constexpr uint8_t ItemCount = sizeof(Items) / sizeof(Items[0]);

	struct {
		lv_obj_t* container;
		LVGIF* gif;
		lv_obj_t* labelContainer;
		lv_obj_t* label;
	} itemContainers[ItemCount];

	static constexpr const char* ConnectedGifPath = "S:/mainMenu/connected";
	LVGIF* connectedGif;
	static constexpr const char* RingingGifPath = "S:/mainMenu/ring";
	static constexpr const char* RingLabelPath = "S:/mainMenu/labels/ringing.bin";
	LVGIF* ringingGif;


	LVStyle textStyle;
	LVStyle subtextStyle;
	LVStyle debugStyle;
	const lv_color_t TextColor = lv_color_make(244, 126, 27);
	const lv_color_t SubtextColor = lv_color_make(207, 198, 184);


};


#endif //CLOCKSTAR_FIRMWARE_MAINMENU_H
