#include "stdafx.h"
#include <esp_timer.h>
#include <esp_heap_caps.h>

uint64_t millis(){
	return micros() / 1000;
}

uint64_t micros(){
	return esp_timer_get_time();
}

void ramReport(){
	printf("Free INTERNAL heap: %zu B, largest block %zu B\n", heap_caps_get_free_size(MALLOC_CAP_INTERNAL), heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL));
	// printf("Free PSRAM heap: %zu B, largest block %zu B\n", heap_caps_get_free_size(MALLOC_CAP_SPIRAM), heap_caps_get_largest_free_block(MALLOC_CAP_SPIRAM));
}
