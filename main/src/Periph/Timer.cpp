#include "Timer.h"
#include <soc/rtc.h>

#include <utility>

Timer::Timer(uint32_t period, std::function<void(void*)> ISR, void* dataPtr) : ISR(std::move(ISR)), dataPtr(dataPtr){

	ESP_ERROR_CHECK(gptimer_new_timer(&timer_config, &gptimer));
	gptimer_event_callbacks_t cbs = {
			.on_alarm = interrupt,
	};
	ESP_ERROR_CHECK(gptimer_register_event_callbacks(gptimer, &cbs, this));
	ESP_ERROR_CHECK(gptimer_enable(gptimer));
	gptimer_alarm_config_t alarm_config = {
			.alarm_count = period * 1000, // period in us
			.reload_count = 0
	};
	alarm_config.flags.auto_reload_on_alarm = 1;

	ESP_ERROR_CHECK(gptimer_set_alarm_action(gptimer, &alarm_config));
}

Timer::~Timer(){
	stop();
	gptimer_disable(gptimer);
	gptimer_del_timer(gptimer);
}


bool Timer::interrupt(gptimer_handle_t timer, const gptimer_alarm_event_data_t* edata, void* user_ctx){
	auto timerObject = (Timer*) user_ctx;
	auto cb = timerObject->ISR;
	if(cb) cb(timerObject->dataPtr);

	return TaskPriority;
}

void Timer::start(){
	ESP_ERROR_CHECK(gptimer_start(gptimer));
}

void Timer::stop(){
	ESP_ERROR_CHECK(gptimer_stop(gptimer));
}

void Timer::reset(){
	ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, 0));
}
