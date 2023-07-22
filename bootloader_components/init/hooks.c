#include "esp_attr.h"
#include "hal/gpio_hal.h"

/** Function used to tell the linker to include this file with all its symbols. */
void bootloader_hooks_include(void){}

void IRAM_ATTR bootloader_before_init(void){
	/* Keep in my mind that a lot of functions cannot be called from here
	 * as system initialization has not been performed yet, including
     * BSS, SPI flash, or memory protection. */
	// ESP_LOGI("HOOK", "This hook is called BEFORE bootloader initialization");

	gpio_ll_input_enable(&GPIO, GPIO_NUM_13);
	gpio_ll_pulldown_dis(&GPIO, GPIO_NUM_13);
	gpio_ll_pullup_dis(&GPIO, GPIO_NUM_13);

	gpio_ll_output_enable(&GPIO, GPIO_NUM_4);
	gpio_ll_set_level(&GPIO, GPIO_NUM_4, 1);
}

void bootloader_after_init(void){
	// ESP_LOGI("HOOK", "This hook is called AFTER bootloader initialization");
}
