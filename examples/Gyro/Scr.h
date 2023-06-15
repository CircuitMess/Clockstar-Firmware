#ifndef CLOCKSTAR_FIRMWARE_SCR_H
#define CLOCKSTAR_FIRMWARE_SCR_H

#include "Devices/IMU.h"
#include "LV_Interface/LVScreen.h"
#include "Util/Queue.h"
#include "Util/Threaded.h"
#include "Util/Events.h"
#include <string>

class Scr : public LVScreen {
public:
	Scr(IMU& imu);
	virtual ~Scr();

private:
	IMU& imu;

	lv_style_t textStyle;

	lv_obj_t* gyroX;
	lv_obj_t* gyroY;
	lv_obj_t* gyroZ;
	lv_obj_t* singleTap;
	lv_obj_t* sigMotion;
	lv_obj_t* wristTilt;

	struct {
		uint32_t singleTap = 0;
		uint32_t sigMotion = 0;
		uint32_t wristTilt = 0;
	} counts;

	void loop() override;

	EventQueue evtQueue;
	ThreadedClosure evtChecker;
	void check();

	ThreadedClosure gyroUpdater;
	void gyroUpdate();

	struct TextRequest {
		lv_obj_t* label;
		std::string text;
		TextRequest(lv_obj_t* label, std::string text) : label(label), text(std::move(text)){}
	};
	PtrQueue<TextRequest> textQueue;
	void requestText(lv_obj_t* label, std::string text);
	void requestText(lv_obj_t* label, std::string text, uint32_t count);

};


#endif //CLOCKSTAR_FIRMWARE_SCR_H
