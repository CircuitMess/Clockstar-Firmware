#ifndef CIRCUITOS_PIEZO_H
#define CIRCUITOS_PIEZO_H

#include <driver/timer.h>
#include <driver/ledc.h>

class PWM {
public:
	PWM(uint8_t pin, ledc_channel_t channel);

	void setFreq(uint16_t freq);
	void stop();

private:
	void attach();
	void detach();
	uint8_t pin = -1;
	ledc_channel_t channel = LEDC_CHANNEL_0;
	static constexpr ledc_mode_t speedMode = LEDC_LOW_SPEED_MODE;
	static constexpr ledc_timer_config_t ledc_timer = {
			.speed_mode       = speedMode,
			.duty_resolution  = LEDC_TIMER_10_BIT,
			.timer_num        = LEDC_TIMER_0,
			.freq_hz          = 5000,  // Set output frequency at 5 kHz
			.clk_cfg          = LEDC_AUTO_CLK
	};
};

#endif //CIRCUITOS_PIEZO_H
