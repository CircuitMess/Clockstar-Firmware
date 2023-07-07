#include <esp_clk_tree.h>
#include <esp_log.h>
#include "PWM.h"

static const char* TAG = "PMW";

PWM::PWM(uint8_t pin, ledc_channel_t channel) : pin(pin), channel(channel){

	ledc_timer_config_t ledc_timer = {
			.speed_mode       = getSpeedMode(channel),
			.duty_resolution  = DutyResDefault,
			.timer_num        = getTimer(channel),
			.freq_hz          = DefaultFreq,
			.clk_cfg          = LEDC_AUTO_CLK
	};
	if(ledc_timer_config(&ledc_timer) != ESP_OK){
		ESP_LOGE(TAG, "timer config failed!");
		return;
	}
}

PWM::~PWM(){
	stop();
}

void PWM::setFreq(uint16_t freq){
	if(pin == (uint8_t) -1) return;

	attach();

	if(!checkFrequency(freq)){
		ESP_LOGW(TAG, "couldnt write frequency %d because of clock divisor limitations, divParam: %lld\n", freq, divParam);
		return;
	}

	auto group = getSpeedMode(channel);
	auto timer = getTimer(channel);

	ledc_set_freq(group, timer, freq);
	ledc_set_duty(group, channel, FullDuty);
	ledc_update_duty(group, channel);
}


constexpr bool PWM::checkFrequency(uint16_t freq){
	uint64_t divParam = 0;
	uint32_t precision = (0x1 << DutyResDefault); // 2**depth

	divParam = (((uint64_t) src_clk_freq << 8) + ((freq * precision) / 2)) / (freq * precision);

	if(!(divParam > 256 && divParam < (0x3FFFF))){
		return false;
	}
	return true;
}

void PWM::stop(){
	if(pin == (uint8_t) -1) return;
	detach();
}

void PWM::attach(){
	if(pin == (uint8_t) -1) return;

	uint8_t group = (channel / 8);
	uint8_t timer = ((channel / 2) % 4);
	ledc_channel_config_t ledc_channel = {
			.gpio_num       = pin,
			.speed_mode     = static_cast<ledc_mode_t>(group),
			.channel        = channel,
			.intr_type      = LEDC_INTR_DISABLE,
			.timer_sel      = static_cast<ledc_timer_t>(timer),
			.duty           = 0,
			.hpoint         = 0,
			.flags = { .output_invert = 1 }
	};
	ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void PWM::detach(){
	ledc_stop(getSpeedMode(channel), channel, 0);
}

constexpr ledc_mode_t PWM::getSpeedMode(ledc_channel_t channel){
	return static_cast<ledc_mode_t>((channel / 8));
}

constexpr ledc_timer_t PWM::getTimer(ledc_channel_t channel){
	return static_cast<ledc_timer_t>(((channel / 2) % 4));
}

