#include "Input.h"
#include "Util/Events.h"
#include <Util/stdafx.h>
#include <Pins.hpp>
#include <driver/gpio.h>

// button index -> GPIO port
const std::unordered_map<Input::Button, gpio_num_t> Input::PinMap{
		// { Up,     (gpio_num_t) BTN_UP },
		{ Down,   (gpio_num_t) BTN_DOWN },
		{ Select, (gpio_num_t) BTN_SELECT },
		{ Alt,    (gpio_num_t) BTN_ALT }
};

const std::unordered_map<Input::Button, const char*> Input::PinLabels{
		{ Up,     "Up" },
		{ Down,   "Down" },
		{ Select, "Select" },
		{ Alt,    "Alt" },
};

Input::Input() : Threaded("Input", 4 * 1024, 6, 1){
	for(const auto& pair : PinMap){
		const auto port = pair.first;
		const auto pin = pair.second;

		btnState[port] = false;
		dbTime[port] = 0;

		gpio_set_direction(pin, GPIO_MODE_INPUT);
		gpio_set_pull_mode(pin, GPIO_PULLDOWN_ONLY);
	}

	start();
}

Input::~Input(){
	stop();
}

void Input::loop(){
	scan();
	vTaskDelay(100);
}

void Input::scan(){
	for(const auto& pair: PinMap){
		const auto port = pair.first;
		const auto pin = pair.second;

		bool state = gpio_get_level(pin);

		if(state){
			pressed(port);
		}else{
			released(port);
		}
	}
}

void Input::pressed(Input::Button btn){
	if(btnState[btn]){
		dbTime[btn] = 0;
		return;
	}

	auto t = millis();

	if(dbTime[btn] == 0){
		dbTime[btn] = t;
		return;
	}else if(t - dbTime[btn] < DebounceTime){
		return;
	}

	btnState[btn] = true;
	dbTime[btn] = 0;

	Data data = {
			.btn = btn,
			.action = Data::Press
	};
	Events::post(Facility::Input, data);
}

void Input::released(Input::Button btn){
	if(!btnState[btn]){
		dbTime[btn] = 0;
		return;
	}

	auto t = millis();

	if(dbTime[btn] == 0){
		dbTime[btn] = t;
		return;
	}else if(t - dbTime[btn] < DebounceTime){
		return;
	}

	btnState[btn] = false;
	dbTime[btn] = 0;

	Data data = {
			.btn = btn,
			.action = Data::Release
	};
	Events::post(Facility::Input, data);
}
