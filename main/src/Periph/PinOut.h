#ifndef CLOCKSTAR_FIRMWARE_PINOUT_H
#define CLOCKSTAR_FIRMWARE_PINOUT_H

#include <hal/gpio_types.h>

class PinOut {
public:
	PinOut(gpio_num_t pin, bool inverted = false);
	PinOut(int pin, bool inverted = false);

	void on();
	void off();
	void set(bool state);

private:
	gpio_num_t pin;
	bool inverted;

};


#endif //CLOCKSTAR_FIRMWARE_PINOUT_H
