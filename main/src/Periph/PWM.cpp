#include <esp_clk_tree.h>
#include <esp_log.h>
#include "PWM.h"

static const char* TAG = "PMW";

PWM::PWM(uint8_t pin, ledc_channel_t channel) : pin(pin), channel(channel){
	ledc_timer_config(&ledc_timer);

}

void PWM::setFreq(uint16_t freq){
	if(pin == (uint8_t) -1) return;

	attach();
	uint64_t divParam;
	uint32_t precision = (0x1 << DutyResDefault); // 2**depth
	uint32_t src_clk_freq;
	esp_clk_tree_src_get_freq_hz((soc_module_clk_t) LEDC_SLOW_CLK_APB, ESP_CLK_TREE_SRC_FREQ_PRECISION_CACHED, &src_clk_freq);
	divParam = (((uint64_t) src_clk_freq << 8) + ((freq * precision) / 2)) / (freq * precision);

	if(!(divParam > 256 && divParam < (0x3FFFF))){
		ESP_LOGW(TAG, "couldnt write frequency %d because of clock divisor limitations, divParam: %lld\n", freq, divParam);
		return;
	}

	ledc_set_freq(SpeedMode, LEDC_TIMER_0, freq);
	ledc_set_duty(SpeedMode, channel, FullDuty);
	ledc_update_duty(SpeedMode, channel);
}

void PWM::stop(){
	if(pin == (uint8_t) -1) return;
	detach();
}

void PWM::attach(){
	ledc_channel_config_t ledc_channel = {
			.gpio_num       = pin,
			.speed_mode     = SpeedMode,
			.channel        = channel,
			.intr_type      = LEDC_INTR_DISABLE,
			.timer_sel      = Timer,
			.duty           = 0,
			.hpoint         = 0,
			.flags = { .output_invert = 1 }
	};
	ESP_ERROR_CHECK(ledc_channel_config(&ledc_channel));
}

void PWM::detach(){
	ledc_stop(SpeedMode, channel, 0);
}
