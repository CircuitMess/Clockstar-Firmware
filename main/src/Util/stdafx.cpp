#include "stdafx.h"
#include <esp_timer.h>

uint32_t millis(){
	return micros() / 1000;
}

uint32_t micros(){
	return esp_timer_get_time();
}
