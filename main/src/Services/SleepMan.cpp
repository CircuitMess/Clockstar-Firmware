#include "SleepMan.h"
#include "Screens/Lock/LockScreen.h"
#include "Util/Services.h"
#include "Screens/ShutdownScreen.h"
#include <esp_sleep.h>

SleepMan::SleepMan(LVGL& lvgl) : events(12), lvgl(lvgl),
								 imu(*((IMU*) Services.get(Service::IMU))),
								 bl(*((BacklightBrightness*) Services.get(Service::Backlight))),
								 settings(*((Settings*) Services.get(Service::Settings))){
	Events::listen(Facility::Input, &events);
	Events::listen(Facility::Motion, &events);
	Events::listen(Facility::Battery, &events);

	imu.enableTiltDetection(settings.get().motionDetection);
	imu.setTiltDirection(IMU::TiltDirection::Lowered);

	actTime = millis();
}

void SleepMan::goSleep(){
	auto battery = (Battery*) Services.get(Service::Battery);
	if(!battery || battery->isShutdown()) return;

	lvgl.stopScreen();
	imu.setTiltDirection(IMU::TiltDirection::Lifted);

	inSleep = true;
	sleep.sleep([this](){
		if(!nsBlocked){
			lvgl.startScreen([](){ return std::make_unique<LockScreen>(); });
		}
		lv_timer_handler();
	});
	nsBlocked = inSleep = false;

	imu.setTiltDirection(IMU::TiltDirection::Lowered);

	wakeTime = actTime = millis();
	events.reset();
}

void SleepMan::wake(bool blockLock){
	if(!inSleep) return;
	nsBlocked = blockLock;
	xSemaphoreGive(sleep.wakeSem);
}

void SleepMan::shutdown(){
	bl.fadeOut();
	imu.shutdown();

	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_PERIPH, ESP_PD_OPTION_AUTO);
	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_SLOW_MEM, ESP_PD_OPTION_AUTO);
	esp_sleep_pd_config(ESP_PD_DOMAIN_RTC_FAST_MEM, ESP_PD_OPTION_AUTO);
	esp_sleep_pd_config(ESP_PD_DOMAIN_XTAL, ESP_PD_OPTION_AUTO);
	esp_sleep_disable_wakeup_source(ESP_SLEEP_WAKEUP_ALL);
	esp_deep_sleep_start();
}

void SleepMan::loop(){
	checkAutoSleep();
	checkEvents();
}

void SleepMan::checkEvents(){
	Event evt;
	while(events.get(evt, 0)){
		if(evt.facility == Facility::Input){
			auto param = (Input::Data*) evt.data;
			handleInput(*param);
		}else if(evt.facility == Facility::Motion){
			auto param = (IMU::Event*) evt.data;
			handleMotion(*param);
		}

		free(evt.data);
	}
}

void SleepMan::checkAutoSleep(){
	if(!autoSleep) return;

	auto sti = settings.get().sleepTime;
	if(sti >= Settings::SleepSteps) return;

	auto sleepSeconds = Settings::SleepSeconds[settings.get().sleepTime];
	if(sleepSeconds == 0) return;

	if((millis() - actTime) / 1000 < sleepSeconds) return;

	goSleep();
}

void SleepMan::handleInput(const Input::Data& evt){
	actTime = millis();

	if(evt.btn != Input::Alt || !altLock) return;

	if(evt.action == Input::Data::Press){
		if(millis() - wakeTime < WakeCooldown) return;
		altPress = millis();
	}else if(millis() - altPress < AltHoldTime){
		goSleep();
	}
}

void SleepMan::handleMotion(const IMU::Event& evt){
	if(!autoSleep) return;

	const bool wristSleep = settings.get().motionDetection;

	if((evt.action == IMU::Event::WristTilt && evt.wristTiltDir == IMU::TiltDirection::Lowered && wristSleep) || evt.action == IMU::Event::DoubleTap){
		goSleep();
	}
}

void SleepMan::enAltLock(bool altLock){
	SleepMan::altLock = altLock;
}

void SleepMan::enAutoSleep(bool autoSleep){
	SleepMan::autoSleep = autoSleep;
}
