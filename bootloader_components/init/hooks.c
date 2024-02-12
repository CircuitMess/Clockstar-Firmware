#include "esp_attr.h"
#include "hal/gpio_hal.h"

/** Function used to tell the linker to include this file with all its symbols. */
void bootloader_hooks_include(void){}

static const gpio_num_t PWDN = GPIO_NUM_42;
static const gpio_num_t LEDs[] = { 17, 18, 43, 44, 45, 46 };

void setLEDs(){
	for(int i = 0; i < sizeof(LEDs)/sizeof(LEDs[0]); i++){
		const uint8_t pin = LEDs[i];
		gpio_ll_pullup_dis(&GPIO, pin);
		gpio_ll_pulldown_dis(&GPIO, pin);
		gpio_ll_input_disable(&GPIO, pin);

		gpio_ll_output_enable(&GPIO, pin);
		gpio_ll_set_level(&GPIO, pin, 0);
	}
}

void IRAM_ATTR bootloader_before_init(void){
	/* Keep in my mind that a lot of functions cannot be called from here
	 * as system initialization has not been performed yet, including
	 * BSS, SPI flash, or memory protection. */
	// ESP_LOGI("HOOK", "This hook is called BEFORE bootloader initialization");

	gpio_ll_input_enable(&GPIO, PWDN);
	gpio_ll_pulldown_dis(&GPIO, PWDN);
	gpio_ll_pullup_dis(&GPIO, PWDN);

	setLEDs();
}

void bootloader_after_init(void){
	// ESP_LOGI("HOOK", "This hook is called AFTER bootloader initialization");
}
