#include "PWM.h"

PWM::PWM(uint8_t pin, ledc_channel_t channel) : pin(pin), channel(channel){
	ledc_timer_config(&ledc_timer);

}

void PWM::setFreq(uint16_t freq){
	if(pin == (uint8_t) -1) return;

	attach();
	ledc_set_freq(speedMode, LEDC_TIMER_0, freq);
	ledc_set_duty(speedMode, channel, 0x1FF);
	ledc_update_duty(speedMode, channel);
}

void PWM::stop(){
	if(pin == (uint8_t) -1) return;
	detach();
}

void PWM::attach(){
	ledc_channel_config_t ledc_channel = {
			.gpio_num       = pin,
			.speed_mode     = speedMode,
			.channel        = channel,
			.intr_type      = LEDC_INTR_DISABLE,
			.timer_sel      = LEDC_TIMER_0,
			.duty           = 0,
			.hpoint         = 0
	};
	ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void PWM::detach(){
	ledc_stop(speedMode, channel, 0);
}
