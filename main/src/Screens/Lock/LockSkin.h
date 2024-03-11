#ifndef ARTEMIS_FIRMWARE_LOCKSKIN_H
#define ARTEMIS_FIRMWARE_LOCKSKIN_H

#include "LV_Interface/LVObject.h"
#include "UIElements/StatusBar.h"
#include "UIElements/ClockLabelBig.h"
#include "Slider.h"
#include "Item.h"

class LockSkin : public LVObject {
public:
	LockSkin(lv_obj_t* parent, 	lv_group_t* inputGroup);

	inline Slider* getLocker() const { return locker; }
	inline lv_obj_t* getMain() noexcept { return main; }

	void loop();
	void prepare();

	void notifAdd(const Notif& notif);
	void notifRem(uint32_t id);
	void notifsClear();

protected:
	lv_group_t* inputGroup = nullptr;
	lv_obj_t* main = nullptr;
	//StatusBar* status = nullptr;
	PhoneElement* phoneElement;
	BatteryElement* batteryElement;
	lv_obj_t* battery;
	lv_obj_t* statusCenter;
	ClockLabelBig* clock = nullptr;
	lv_obj_t* icons = nullptr;
	Slider* locker = nullptr;
	lv_obj_t* rest = nullptr;
	// TODO change so that notifications are in the notification element type structure

	static constexpr uint8_t MaxNotifs = 20;
	std::unordered_map<uint32_t, Item*> notifs;

	struct NotifIcon {
		uint32_t count;
		lv_obj_t* icon;
	};
	std::unordered_map<const char*, NotifIcon> notifIcons;
	static constexpr uint8_t MaxIconsCount = MaxNotifs;

private:
	void addNotifIcon(const char* path);
	void removeNotifIcon(const char* path);
	void updateNotifs();
	void buildUI();
};

#endif //ARTEMIS_FIRMWARE_LOCKSKIN_H