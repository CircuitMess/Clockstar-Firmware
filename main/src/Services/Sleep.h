#ifndef CLOCKSTAR_FIRMWARE_SLEEP_H
#define CLOCKSTAR_FIRMWARE_SLEEP_H

#include "Devices/Input.h"
#include "Services/Time.h"
#include "Pins.hpp"

class Sleep {
public:
	Sleep(Input& input, Time& time);

	void sleep(std::function<void()> preWake = {});

private:
	Input& input;
	Time& time;

	static constexpr gpio_num_t WakePin = (gpio_num_t) BTN_ALT;

	SemaphoreHandle_t wakeSem;
	static void intr(void* arg);

	void sleepStart();

	void confPM(bool sleep);

};


#endif //CLOCKSTAR_FIRMWARE_SLEEP_H
