#ifndef CLOCKSTAR_FIRMWARE_SCR_H
#define CLOCKSTAR_FIRMWARE_SCR_H

#include "LV_Interface/LVScreen.h"
#include "Devices/RTC.h"
#include "Notifs/ANCS/Client.h"

class Scr : public LVScreen {
public:
	Scr(RTC& rtc, ANCS::Client& ancs);
	virtual ~Scr();

private:
	lv_style_t textStyle;

	lv_obj_t* uptime;
	lv_obj_t* time;
	lv_obj_t* drift;
	lv_obj_t* notif;
	lv_obj_t* batt;
	lv_obj_t* gyro;
	lv_obj_t* stepsKnocks;

	void redraw();

	void drawUptime();
	void drawTime();
	void loop() override;
	uint32_t lastDraw = 0;
	tm startTimeRtc;
	uint32_t startTimeSystem;

	RTC rtc;
	ANCS::Client& ancs;

	struct TextRequest {
		lv_obj_t* label;
		char* text;
	};
	QueueHandle_t textQueue;
	void requestText(lv_obj_t* label, std::string text);

};


#endif //CLOCKSTAR_FIRMWARE_SCR_H
