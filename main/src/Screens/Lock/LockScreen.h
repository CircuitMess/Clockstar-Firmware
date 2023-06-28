#ifndef CLOCKSTAR_FIRMWARE_LOCKSCREEN_H
#define CLOCKSTAR_FIRMWARE_LOCKSCREEN_H

#include "LV_Interface/LVScreen.h"
#include "Util/Events.h"
#include "Notifs/Phone.h"
#include "Item.h"

class LockScreen : public LVScreen {
public:
	LockScreen();
	void onStarting() override;

private:
	lv_obj_t* bg;

	/** Layout:
	 *
	 * - main
	 * |-- mainTop
	 * |-- mainMid
	 * | |- clock
	 * | |- date
	 * | `- icons
	 * `-- mainBot
	 *
	 * - rest
	 * |-- item
	 * |-- item
	 * `-- item
	 */

	lv_obj_t* main;

	lv_obj_t* mainTop;

	lv_obj_t* mainMid;
	lv_obj_t* clock;
	lv_obj_t* date;
	lv_obj_t* icons;

	lv_obj_t* mainBot;
	lv_obj_t* playing;
	lv_obj_t* lock;

	lv_obj_t* rest;

	Phone& phone;
	EventQueue queue;

	struct NotifEl {
		Notif notif;
		lv_obj_t* icon;
		std::unique_ptr<Item> item;
	};
	std::unordered_map<uint32_t, NotifEl> notifs;
	lv_obj_t* moreIcon;

	void notifAdd(const Notif& notif);
	void notifRem(uint32_t id);
	void notifsClear();

	void loop() override;
	void processEvt(const Phone::Event& evt);

	void updateTime(const tm& time);
	static constexpr uint32_t TimeUpdateInterval = 200;
	uint64_t lastTimeUpdate = 0;

	void buildUI();

};


#endif //CLOCKSTAR_FIRMWARE_LOCKSCREEN_H
