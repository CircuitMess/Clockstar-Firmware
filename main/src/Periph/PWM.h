#ifndef CIRCUITOS_PIEZO_H
#define CIRCUITOS_PIEZO_H

#include <driver/gptimer.h>
#include <driver/ledc.h>
#include <esp_attr.h>

/**
 * Duty resolution defaults to 10-bit (usually enough for most uses such as a piezo buzzer or LED dimming).
 *
 *
 * LEDC Chan to Group/Channel/Timer Mapping (used to prevent conflicts between channels/timers/groups)
** ledc: 0  => Group: 0, Channel: 0, Timer: 0
** ledc: 1  => Group: 0, Channel: 1, Timer: 0
** ledc: 2  => Group: 0, Channel: 2, Timer: 1
** ledc: 3  => Group: 0, Channel: 3, Timer: 1
** ledc: 4  => Group: 0, Channel: 4, Timer: 2
** ledc: 5  => Group: 0, Channel: 5, Timer: 2
** ledc: 6  => Group: 0, Channel: 6, Timer: 3
** ledc: 7  => Group: 0, Channel: 7, Timer: 3
** ledc: 8  => Group: 1, Channel: 0, Timer: 0
** ledc: 9  => Group: 1, Channel: 1, Timer: 0
** ledc: 10 => Group: 1, Channel: 2, Timer: 1
** ledc: 11 => Group: 1, Channel: 3, Timer: 1
** ledc: 12 => Group: 1, Channel: 4, Timer: 2
** ledc: 13 => Group: 1, Channel: 5, Timer: 2
** ledc: 14 => Group: 1, Channel: 6, Timer: 3
** ledc: 15 => Group: 1, Channel: 7, Timer: 3
 */

class PWM {
public:
	PWM(uint8_t pin, ledc_channel_t channel, bool invertDuty = false);
	virtual ~PWM();

	void setFreq(uint16_t freq);
	void setDuty(uint8_t perc); //duty in percentage (0 - 100%)
	void stop();

	void attach();
	void detach();

	static constexpr bool IRAM_ATTR checkFrequency(uint16_t freq){
		uint64_t divParam = 0;
		uint32_t precision = FullDuty;

		divParam = (((uint64_t) src_clk_freq << 8) + ((freq * precision) / 2)) / (freq * precision);

		if(!(divParam > 256 && divParam < (0x3FFFF))){
			return false;
		}
		return true;
	}

private:
	uint8_t pin = -1;
	ledc_channel_t channel = LEDC_CHANNEL_0;
	bool invertDuty = false;
	bool attached = false;

	static constexpr uint32_t DefaultFreq = 5000;    //placeholder, usually changed before attaching to a channel or pin

	static constexpr ledc_timer_bit_t DRAM_ATTR DutyResDefault = LEDC_TIMER_10_BIT;
	static constexpr uint32_t DRAM_ATTR FullDuty = 1 << DutyResDefault;

	static constexpr ledc_mode_t getSpeedMode(ledc_channel_t channel);
	static constexpr ledc_timer_t getTimer(ledc_channel_t channel);
	static constexpr uint32_t DRAM_ATTR src_clk_freq = 80000000; //80 MHz
};

#endif //CIRCUITOS_PIEZO_H
