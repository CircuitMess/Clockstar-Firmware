#ifndef CLOCKSTAR_FIRMWARE_BACKLIGHTBRIGHTNESS_H
#define CLOCKSTAR_FIRMWARE_BACKLIGHTBRIGHTNESS_H

#include "Periph/PWM.h"
#include "Settings/Settings.h"

class BacklightBrightness {
public:
	explicit BacklightBrightness(PWM* pwm);
	void setBrightness(uint8_t level); //0 - 100%

	void fadeIn();
	void fadeOut();

	bool isOn();

private:
	PWM& pwm;
	static constexpr uint8_t mapDuty(uint8_t level);
	static constexpr uint8_t FadeDelay = 2;
	static constexpr uint8_t MinDuty = 10;

	bool state = false;
};


#endif //CLOCKSTAR_FIRMWARE_BACKLIGHTBRIGHTNESS_H
