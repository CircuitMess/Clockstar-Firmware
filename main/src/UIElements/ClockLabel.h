#ifndef CLOCKSTAR_FIRMWARE_CLOCKLABEL_H
#define CLOCKSTAR_FIRMWARE_CLOCKLABEL_H

#include "LV_Interface/LVObject.h"
#include "Services/Time.h"
#include "Util/Events.h"

class ClockLabel : public LVObject {
public:
	explicit ClockLabel(lv_obj_t* parent);
	~ClockLabel() override;

	void loop();

protected:
	void updateTime(const tm& time);

	Time& ts;

private:
	virtual void updateUI(const char* clockText) = 0;

	EventQueue queue;

	static constexpr uint32_t TimeUpdateInterval = 200;
	uint64_t lastTimeUpdate = 0;
};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABEL_H
