#ifndef CIRCUITOS_PIEZO_H
#define CIRCUITOS_PIEZO_H

#include <driver/gptimer.h>
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
	static constexpr ledc_mode_t SpeedMode = LEDC_LOW_SPEED_MODE;
	static constexpr ledc_timer_t Timer = LEDC_TIMER_0;
	ledc_timer_config_t ledc_timer = {
			.speed_mode       = SpeedMode,
			.duty_resolution  = DutyResDefault,
			.timer_num        = LEDC_TIMER_0,
			.freq_hz          = 5000,
			.clk_cfg          = LEDC_AUTO_CLK
	};
	static constexpr ledc_timer_bit_t DutyResDefault = LEDC_TIMER_10_BIT;
	static constexpr uint32_t FullDuty = (1 << (LEDC_TIMER_10_BIT - 1)) - 1;
};

#endif //CIRCUITOS_PIEZO_H
