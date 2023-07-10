#ifndef CLOCKSTAR_FIRMWARE_TIMER_H
#define CLOCKSTAR_FIRMWARE_TIMER_H

#include <driver/gptimer.h>
#include <functional>
#include <esp_attr.h>

/**
 * ESP Timer HAL takes care of HW allocation when Timers are created. (No need to specify timerID and timerGroup)
 * The HW has 4 timers, so construction of more will fail.
 */

class Timer {
public:
	/**
	 * @param period - Time between ISR calls [ms]
	 * @param ISR - ISR routine to be called when period time runs out. Must be non-blocking (using fromISR functions)
	 * @param dataPtr - data pointer passed to ISR routine, optional
	 */
	Timer(uint32_t period, std::function<void(void*)> ISR, void* dataPtr = nullptr);
	virtual ~Timer();

	void start();
	void stop();
	void reset();
	void setPeriod(uint32_t period);

private:
	static bool IRAM_ATTR interrupt(gptimer_handle_t timer, const gptimer_alarm_event_data_t* edata, void* user_ctx);

	static constexpr bool TaskPriority = false;
	enum {
		Stopped, Running
	} state = Stopped;

	gptimer_handle_t gptimer = nullptr;

	gptimer_config_t timer_config = {
			.clk_src = GPTIMER_CLK_SRC_DEFAULT,
			.direction = GPTIMER_COUNT_UP,
			.resolution_hz = 1000000, // 1MHz, 1 tick=1us
			.flags = { .intr_shared = 0 }
	};

	std::function<void(void*)> ISR;
	void* dataPtr;
};


#endif //CLOCKSTAR_FIRMWARE_TIMER_H
