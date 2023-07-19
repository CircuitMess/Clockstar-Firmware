#include "StatusCenter.h"
#include "Util/Services.h"
#include "Pins.hpp"

StatusCenter::StatusCenter() : Threaded("Status", 2048), events(12),
chirp(*((ChirpSystem*) Services.get(Service::Audio))),
settings(*((Settings*) Services.get(Service::Settings))),
phone(*((Phone*) Services.get(Service::Phone)))
{
	Events::listen(Facility::Phone, &events);
	Events::listen(Facility::Battery, &events);

	auto pwmR = new PWM(RGB_R, LEDC_CHANNEL_2, true);
	auto pwmG = new PWM(RGB_G, LEDC_CHANNEL_3, true);
	auto pwmB = new PWM(RGB_B, LEDC_CHANNEL_4, true);

	led = new RGBLEDController(*pwmR, *pwmG, *pwmB);

	updateLED();
	start();
}

void StatusCenter::loop(){
	Event evt;
	if(!events.get(evt, portMAX_DELAY)) return;

	if(evt.facility == Facility::Phone){
		auto data = (Phone::Event*) evt.data;
		processPhone(*data);
	}else if(evt.facility == Facility::Battery){
		auto data = (Battery::Event*) evt.data;
		processBatt(*data);
	}

	free(evt.data);
}

void StatusCenter::processPhone(const Phone::Event& evt){
	hasNotifs = !phone.getNotifs().empty();

	if((evt.action == Phone::Event::Added || evt.action == Phone::Event::Changed) && settings.get().notificationSounds && !audioBlocked){
		chirp.play({
			Chirp { .startFreq = 800, .endFreq = 1000, .duration = 100 },
			Chirp { .startFreq = 0, .endFreq = 0, .duration = 100 },
			Chirp { .startFreq = 1000, .endFreq = 1000, .duration = 100 },
			Chirp { .startFreq = 0, .endFreq = 0, .duration = 150 },
			Chirp { .startFreq = 1000, .endFreq = 1000, .duration = 100 },
			Chirp { .startFreq = 0, .endFreq = 0, .duration = 100 },
			Chirp { .startFreq = 1000, .endFreq = 800, .duration = 100 }
		});
	}

	if(settings.get().ledEnable){
		blink();
	}

	updateLED();
}

void StatusCenter::processBatt(const Battery::Event& evt){
	if(evt.action == Battery::Event::BatteryLow){
		battState = Empty;
	}else if(evt.action == Battery::Event::Charging){
		if(evt.chargeStatus){
			battState = Charging;
		}else{
			battState = Ok;
		}
	}

	updateLED();
}

void StatusCenter::updateLED(){
	if(settings.get().ledEnable == false){
		led->clear();
		return;
	}

	if(battState == Empty){
		led->blinkContinuous({ 255, 0, 0 }, 100, 3000);
	}else if(battState == Charging){
		led->breathe({ 40, 250, 0 }, { 60, 230, 0 }, 6000);
	}else if(battState == Ok){
		led->clear();
	}
}

void StatusCenter::blockAudio(bool block){
	this->audioBlocked = block;
}

void StatusCenter::blink(){
	led->blinkTwice({ 0, 0, 255 });
}
