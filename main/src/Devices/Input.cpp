#include "Input.h"
#include "Util/Events.h"
#include <Util/stdafx.h>
#include <Pins.hpp>
#include <driver/gpio.h>

// button index -> GPIO port
const std::unordered_map<Input::Button, gpio_num_t> Input::PinMap{
		{ Up,     (gpio_num_t) BTN_UP },
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

Input::Input() : SleepyThreaded(SleepTime, "Input", 1024, 6, 0){
	auto mask = 0ULL;
	for(const auto& pair : PinMap){
		const auto port = pair.first;
		const auto pin = pair.second;

		btnState[port] = false;
		dbTime[port] = 0;

		mask |= (1ULL << pin);
	}

	gpio_config_t io_conf = {
			.pin_bit_mask = mask,
			.mode = GPIO_MODE_INPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_ENABLE,
			.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&io_conf);

	start();
}

Input::~Input(){
	stop();
}

void Input::sleepyLoop(){
	scan();
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
