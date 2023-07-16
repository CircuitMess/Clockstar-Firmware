#include "Timer.h"

Timer::Timer(uint32_t period, TimerCallback ISR, void* dataPtr) : ISR(ISR), dataPtr(dataPtr){

	gptimer_new_timer(&timer_config, &gptimer);
	gptimer_event_callbacks_t cbs = {
			.on_alarm = interrupt,
	};
	gptimer_register_event_callbacks(gptimer, &cbs, this);
	gptimer_enable(gptimer);
	setPeriod(period);
}

Timer::~Timer(){
	stop();
	gptimer_disable(gptimer);
	gptimer_del_timer(gptimer);
}


void IRAM_ATTR Timer::start(){
	if(state == Running) return;

	state = Running;
	gptimer_start(gptimer);
}

void IRAM_ATTR Timer::stop(){
	if(state == Stopped) return;

	state = Stopped;
	gptimer_stop(gptimer);
}

void IRAM_ATTR Timer::reset(){
	gptimer_set_raw_count(gptimer, 0);
}

void IRAM_ATTR Timer::setPeriod(uint32_t period){
	gptimer_alarm_config_t alarm_config = {
			.alarm_count = period * 1000, // period in us
			.reload_count = 0,
			.flags = { .auto_reload_on_alarm = 1 }
	};
	gptimer_set_alarm_action(gptimer, &alarm_config);
}

bool IRAM_ATTR Timer::interrupt(gptimer_handle_t timer, const gptimer_alarm_event_data_t* edata, void* user_ctx){
	auto timerObject = (Timer*) user_ctx;
	TimerCallback cb = timerObject->ISR;
	if(cb != nullptr) cb(timerObject->dataPtr);

	return false;
}
