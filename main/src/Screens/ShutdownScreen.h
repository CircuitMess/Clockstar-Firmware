#ifndef CLOCKSTAR_FIRMWARE_SHUTDOWNSCREEN_H
#define CLOCKSTAR_FIRMWARE_SHUTDOWNSCREEN_H


#include "LV_Interface/LVScreen.h"

class ShutdownScreen : public LVScreen {
public:
	ShutdownScreen();

private:
	void loop() override;
	void onStart() override;

	void shutdown();

	lv_obj_t* label;
	lv_obj_t* img;
	lv_obj_t* bg;

	static constexpr uint32_t ShutdownTime = 4000;
	static constexpr uint32_t BlinkPeriod = 350;
	uint32_t blinkTime = 0;
	uint32_t shutdownTime = 0;
};


#endif //CLOCKSTAR_FIRMWARE_SHUTDOWNSCREEN_H
