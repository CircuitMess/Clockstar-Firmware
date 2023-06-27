#include "Time.h"
#include "Util/stdafx.h"
#include "Util/Events.h"

Time::Time(RTC& rtc) : Threaded("Time", 4 * 1024, 6, 0), rtc(rtc){
	updateTime = millis();
	tm time_tm = rtc.getTime();
	time = mktime(&time_tm);
}

std::tm Time::getTime() const{
	time_t currentTime = time + (millis() - updateTime) / 1000;
	tm ret = {};
	gmtime_r(&currentTime, &ret);
	return ret;
}

void Time::setTime(tm time_tm){
	updateTime = millis();

	rtc.setTime(time_tm);
	Time::time = mktime(&time_tm);

	Events::post(Facility::Time, Time::Event { .action = Event::Updated, .updated = { .time = time_tm } });
}

void Time::setTime(time_t time){
	updateTime = millis();

	tm time_tm = {};
	gmtime_r(&time, &time_tm);

	rtc.setTime(time_tm);
	Time::time = time;

	Events::post(Facility::Time, Time::Event { .action = Event::Updated, .updated = { .time = time_tm } });
}

void Time::loop(){
	if(millis() - updateTime < UpdateInterval){
		vTaskDelay(millis() - updateTime + 1);
		return;
	}

	updateTime = millis();
	tm time_tm = rtc.getTime();
	time = mktime(&time_tm);

	Events::post(Facility::Time, Time::Event { .action = Event::Updated, .updated = { .time = time_tm } });

	vTaskDelay(UpdateInterval + 1);
}
