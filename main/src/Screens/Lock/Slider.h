#ifndef CLOCKSTAR_FIRMWARE_SLIDER_H
#define CLOCKSTAR_FIRMWARE_SLIDER_H


#include "LV_Interface/LVObject.h"

class Slider : public LVObject {
public:
	Slider(lv_obj_t* parent);

	void loop();
	void start();
	void stop();

	bool started();
	float t();

private:
	lv_obj_t* icon;

	static constexpr uint32_t Duration = 500; // [ms]
	uint64_t startTime = 0;

};


#endif //CLOCKSTAR_FIRMWARE_SLIDER_H
