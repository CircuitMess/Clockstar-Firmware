#ifndef ARTEMIS_FIRMWARE_LOCKSKIN_H
#define ARTEMIS_FIRMWARE_LOCKSKIN_H

#include "LV_Interface/LVObject.h"
#include "UIElements/StatusBar.h"
#include "UIElements/ClockLabelBig.h"
#include "Slider.h"

class LockSkin : public LVObject {
public:
	LockSkin(lv_obj_t* parent, 	lv_group_t* inputGroup);
	virtual ~LockSkin() override;

	inline StatusBar* getStatusBar() const { return status; }
	inline ClockLabelBig* getClock() const { return clock; }
	inline Slider* getLocker() const { return locker; }
	inline lv_obj_t* getMain() noexcept { return main; }

	void loop();
	void prepare();

private:
	lv_group_t* inputGroup = nullptr;
	lv_obj_t* main = nullptr;
	StatusBar* status = nullptr;
	ClockLabelBig* clock = nullptr;
	lv_obj_t* icons = nullptr;
	Slider* locker = nullptr;
	lv_obj_t* rest = nullptr;

private:
	void buildUI();
};

#endif //ARTEMIS_FIRMWARE_LOCKSKIN_H