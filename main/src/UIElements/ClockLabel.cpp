#include "ClockLabel.h"
#include "Util/Services.h"
#include "Util/stdafx.h"

ClockLabel::ClockLabel(lv_obj_t* parent) : LVObject(parent), ts(*((Time*) Services.get(Service::Time))), queue(2){
	lv_obj_set_size(obj, LV_SIZE_CONTENT, LV_SIZE_CONTENT);
	clock = lv_label_create(obj);

	Events::listen(Facility::Time, &queue);

	updateTime(ts.getTime());
}

lv_obj_t* ClockLabel::label(){
	return clock;
}

void ClockLabel::loop(){
	if(millis() - lastTimeUpdate > TimeUpdateInterval){
		updateTime(ts.getTime());
	}

	Event evt;
	if(queue.get(evt, 0)){
		if(evt.facility == Facility::Time){
			auto data = (Time::Event*) evt.data;
			if(data->action == Time::Event::Updated){
				updateTime(data->updated.time);
			}
		}
		free(evt.data);
	}
}

void ClockLabel::updateTime(const tm& time){
	lastTimeUpdate = millis();

	char clockText[128];
	snprintf(clockText, sizeof(clockText), "%02d%c%02d", time.tm_hour, time.tm_sec % 2 ? ':' : ' ', time.tm_min);

	lv_label_set_text(clock, clockText);
	lv_obj_refr_size(*this);
	lv_obj_invalidate(*this);
}
