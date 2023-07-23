#include "SleepMan.h"
#include "Screens/Lock/LockScreen.h"

SleepMan::SleepMan(LVGL& lvgl) : lvgl(lvgl), events(12){
	Events::listen(Facility::Input, &events);
	Events::listen(Facility::Motion, &events);
}

void SleepMan::loop(){
	Event evt;
	if(!events.get(evt, 0)) return;

	if(evt.facility == Facility::Input){
		auto param = (Input::Data*) evt.data;
		handleInput(*param);
	}else if(evt.facility == Facility::Motion){
		auto param = (IMU::Event*) evt.data;
		handleMotion(*param);
	}

	free(evt.data);
}

void SleepMan::handleInput(const Input::Data& evt){
	if(evt.btn != Input::Alt || !altLock) return;

	if(evt.action == Input::Data::Press){
		if(millis() - wakeTime < AltHoldCooldown) return;
		altPress = millis();
	}else if(millis() - altPress < AltHoldTime){
		sleep.sleep([this](){
			lvgl.startScreen([](){ return std::make_unique<LockScreen>(); });
			lv_timer_handler();
		});
		events.reset();
		wakeTime = millis();
	}
}

void SleepMan::handleMotion(const IMU::Event& evt){

}

void SleepMan::enAltLock(bool altLock){
	SleepMan::altLock = altLock;
}
