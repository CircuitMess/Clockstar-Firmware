#include <driver/gpio.h>
#include "Pins.hpp"
#include "Periph/I2C.h"
#include "Periph/PinOut.h"
#include "Devices/Display.h"
#include "LV_Interface/LVGL.h"

#include <lvgl/lvgl.h>

void init(){
	gpio_config_t io_conf = {
			.pin_bit_mask = 1 << 13,
			.mode = GPIO_MODE_INPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&io_conf);

	auto bl = new PinOut(PIN_BL, true);
	bl->on();

	auto i2c = new I2C(0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);

	auto disp = new Display();
	auto lvgl = new LVGL(*disp);

	// Load start screen here
	auto scr = lv_obj_create(nullptr);
	lv_scr_load(scr);

	// Start UI thread after initialization
	lvgl->start();
}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
