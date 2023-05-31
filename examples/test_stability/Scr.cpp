#include "Scr.h"
#include "lgfx/v0/platforms/esp32_common.hpp"
#include <sstream>
#include <iomanip>

Scr::Scr(RTC& rtc, ANCS::Client& ancs, Battery& battery, IMU& imu) : rtc(rtc), ancs(ancs), battery(battery), imu(imu),
																	 IMUPoller([this, &imu](){
																		 float res;
																		 std::stringstream ss;
																		 if(!imu.getXTilt(&res)){
																			 IMUErrCount++;
																			 ss << "Errors: " << IMUErrCount;
																			 requestText(IMUErrors, ss.str());
																		 }else{
																			 ss << "X tilt: " << std::setprecision(3) << res;
																			 requestText(gyro, ss.str());
																		 }
																		 vTaskDelay(100 / portTICK_PERIOD_MS);
																	 }, "IMUPoller"){
	startTimeSystem = millis();
	startTimeRtc = rtc.getTime();

	lv_obj_set_size(obj, 128, 128);
	lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);

	lv_style_init(&textStyle);
	lv_style_set_text_color(&textStyle, lv_color_white());
	lv_style_set_text_font(&textStyle, &lv_font_unscii_8);
	lv_style_set_width(&textStyle, LV_PCT(100));

	textQueue = xQueueCreate(12, sizeof(TextRequest));

	for(auto text: { &time, &uptime, &drift, &notif, &batt, &gyro, &stepsKnocks, &IMUErrors }){
		*text = lv_label_create(obj);
		lv_obj_add_style(*text, &textStyle, 0);
		lv_label_set_text(*text, "");
		lv_label_set_long_mode(*text, LV_LABEL_LONG_SCROLL_CIRCULAR);
	}

	auto replaceNotif = [this](Notif notif){
		std::stringstream text;
		text << "Notif: " << notif.title << ": " << notif.message;
		requestText(this->notif, text.str());
	};
	ancs.setOnNotifAdd(replaceNotif);
	ancs.setOnNotifModify(replaceNotif);
	ancs.setOnNotifRemove([this](uint32_t uid){ requestText(notif, "Notif cleared."); });

	requestText(notif, "Phone not connected.");
	ancs.setOnConnect([this](){ requestText(notif, "Phone connected."); });
	ancs.setOnDisconnect([this](){ requestText(notif, "Phone connection broken."); });

	auto replaceSteps = [this](){
		std::stringstream text;
		text << "Steps: " << stepCount << " Knocks: " << knockCount;
		requestText(stepsKnocks, text.str());
	};
	replaceSteps();

	imu.onKnock([this, replaceSteps](){
		knockCount++;
		replaceSteps();
	});
	imu.onStep([this, replaceSteps](){
		stepCount++;
		replaceSteps();
	});
	IMUPoller.start();
	requestText(IMUErrors, "Errors: 0");


	redraw();
}

Scr::~Scr(){
	vQueueDelete(textQueue);
}

void Scr::loop(){
	if(millis() - lastDraw > 1000){
		redraw();
		lastDraw = millis();
	}

	TextRequest request;
	while(xQueueReceive(textQueue, &request, 0) == pdTRUE){
		lv_label_set_text(request.label, request.text);
		free(request.text);
	}
}

void Scr::requestText(lv_obj_t* label, std::string text){
	auto buf = (char*) malloc(text.size() + 1);
	buf[text.size()] = 0;
	memcpy(buf, text.data(), text.size());
	TextRequest request = { .label = label, .text = buf };
	xQueueSend(textQueue, &request, portMAX_DELAY);
}

void Scr::redraw(){
	drawUptime();
	drawTime();
	drawBatt();
}

void Scr::drawUptime(){
	uint32_t uptime = millis();
	uint32_t seconds = uptime / 1000;
	uint32_t minutes = seconds / 60;
	uint32_t hours = minutes / 60;
	uint32_t days = hours / 24;
	hours -= days * 24;
	minutes -= days * 24 * 60 + hours * 60;
	seconds -= days * 24 * 60 * 60 + hours * 60 * 60 + minutes * 60;

	std::stringstream text;
	text << "Uptime: ";

	if(hours > 0){
		text << hours << "h, ";
	}
	if(minutes > 0){
		text << minutes << "m, ";
	}
	text << seconds << "s";

	requestText(this->uptime, text.str());

	uptime = millis();
	auto rtcTime = rtc.getTime();
	auto rtcUptime = difftime(mktime(&rtcTime), mktime(&startTimeRtc));

	text.str("");
	text << "Drift: " << std::setprecision(3) << ((double) (uptime - startTimeSystem) / 1000.0) - rtcUptime << "s";
	requestText(this->drift, text.str());
}

void Scr::drawTime(){
	auto time = rtc.getTime();
	std::stringstream text;
	text << std::put_time(&time, "%b %d %H:%M:%S");
	requestText(this->time, text.str());
}

void Scr::drawBatt(){
	std::stringstream text;
	text << "Batt: " << (int) battery.getPercentage() << "% USB: " << (battery.isCharging() ? 1 : 0);
	requestText(this->batt, text.str());
}
