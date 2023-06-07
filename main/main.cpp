#include <driver/gpio.h>
#include <nvs_flash.h>
#include "Pins.hpp"
#include "Periph/I2C.h"
#include "Periph/PinOut.h"
#include "Periph/Bluetooth.h"
#include "Devices/Display.h"
#include "LV_Interface/LVGL.h"
#include "BLE/GAP.h"
#include "BLE/Client.h"
#include "Devices/IMU/IMU.h"
#include <lvgl/lvgl.h>
#include <esp_sleep.h>
#include <driver/uart.h>

void init(){
	gpio_config_t io_conf = {
			.pin_bit_mask = 1 << 13,
			.mode = GPIO_MODE_INPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&io_conf);

	auto ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	auto bl = new PinOut(PIN_BL, true);
	bl->on();

	auto i2c = new I2C(0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);
	auto imu = new IMU(*i2c);

	auto bt = new Bluetooth();
	auto gap = new BLE::GAP();
	auto client = new BLE::Client(gap);

	auto disp = new Display();
	auto lvgl = new LVGL(*disp);

	// Load start screen here
	auto scr = lv_obj_create(nullptr);
	lv_scr_load(scr);

	// Start UI thread after initialization
	lvgl->start();
	imu->init();

}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
