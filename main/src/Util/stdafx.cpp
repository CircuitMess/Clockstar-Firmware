#include "stdafx.h"
#include <esp_timer.h>

uint64_t millis(){
	return micros() / 1000;
}

uint64_t micros(){
	return esp_timer_get_time();
}
