#include "Timer.h"
#include <esp_log.h>

static const char* TAG = "Timer";

Timer::Timer(uint32_t period, TimerCallback ISR, void* dataPtr) : ISR(ISR), dataPtr(dataPtr){
	esp_timer_create_args_t args = {
			.callback = interrupt,
			.arg = this,
			.dispatch_method = ESP_TIMER_ISR,
			.name = "Timer",
			.skip_unhandled_events = true
	};
	ESP_ERROR_CHECK(esp_timer_create(&args, &timer));
	setPeriod(period);
}

Timer::~Timer(){
	stop();
	esp_timer_delete(timer);
}

void IRAM_ATTR Timer::start(){
	if(state == Running) return;
	state = Running;
	esp_timer_start_once(timer, period);
}

void IRAM_ATTR Timer::stop(){
	if(state == Stopped) return;
	state = Stopped;
	esp_timer_stop(timer);
}

void Timer::reset(){
	if(state == Stopped) return;
	esp_timer_restart(timer, period);
}

void IRAM_ATTR Timer::setPeriod(uint32_t period){
	if(state == Running){
		ESP_LOGE(TAG, "setPeriod called while timer is running");
		return;
	}

	this->period = period*1000;
}

void IRAM_ATTR Timer::interrupt(void* arg){
	auto timer = (Timer*) arg;
	timer->state = Stopped;
	timer->ISR(timer->dataPtr);
}
