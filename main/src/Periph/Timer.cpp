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
	setPeriod(period);
}

Timer::~Timer(){
	stop();
	gptimer_disable(gptimer);
	gptimer_del_timer(gptimer);
}


void Timer::start(){
	if(state == Running) return;

	state = Running;
	ESP_ERROR_CHECK(gptimer_start(gptimer));
}

void Timer::stop(){
	if(state == Stopped) return;

	state = Stopped;
	ESP_ERROR_CHECK(gptimer_stop(gptimer));
}

void Timer::reset(){
	ESP_ERROR_CHECK(gptimer_set_raw_count(gptimer, 0));
}

void Timer::setPeriod(uint32_t period){
	gptimer_alarm_config_t alarm_config = {
			.alarm_count = period * 1000, // period in us
			.reload_count = 0,
			.flags = { .auto_reload_on_alarm = 1 }
	};
	gptimer_set_alarm_action(gptimer, &alarm_config);
}

bool IRAM_ATTR Timer::interrupt(gptimer_handle_t timer, const gptimer_alarm_event_data_t* edata, void* user_ctx){
	auto timerObject = (Timer*) user_ctx;
	auto cb = timerObject->ISR;
	if(cb) cb(timerObject->dataPtr);

	return TaskPriority;
}
