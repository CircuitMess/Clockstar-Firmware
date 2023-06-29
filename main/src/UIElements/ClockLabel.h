#ifndef CLOCKSTAR_FIRMWARE_CLOCKLABEL_H
#define CLOCKSTAR_FIRMWARE_CLOCKLABEL_H

#include "LV_Interface/LVObject.h"
#include "Services/Time.h"
#include "Util/Events.h"

class ClockLabel : public LVObject {
public:
	ClockLabel(lv_obj_t* parent);

	void loop();

	lv_obj_t* label();

private:
	Time& ts;
	EventQueue queue;

	lv_obj_t* clock;

	void updateTime(const tm& time);
	static constexpr uint32_t TimeUpdateInterval = 200;
	uint64_t lastTimeUpdate = 0;

};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABEL_H
