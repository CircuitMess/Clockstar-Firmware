#include "PinOut.h"
#include <driver/gpio.h>

PinOut::PinOut(gpio_num_t pin, bool inverted) : PinOut((int)pin, inverted){

}

PinOut::PinOut(int pin, bool inverted) : pin((gpio_num_t) pin), inverted(inverted){
	gpio_config_t cfg = {
			.pin_bit_mask = ((uint64_t) 1) << pin,
			.mode = GPIO_MODE_OUTPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&cfg);
	off();
}

void PinOut::on(){
	set(true);
}

void PinOut::off(){
	set(false);
}

void PinOut::set(bool state){
	gpio_set_level(pin, state ^ inverted);
}
