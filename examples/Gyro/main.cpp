#include <driver/gpio.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include "Pins.hpp"
#include "Periph/I2C.h"
#include "Devices/IMU.h"
#include "Devices/Display.h"
#include "LV_Interface/LVGL.h"
#include "Scr.h"

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

	// esp_log_level_set("BLE", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::Client", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::Service", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::ServiceInfo", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::Char", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::CharInfo", ESP_LOG_VERBOSE);
	// esp_log_level_set("ANCS", ESP_LOG_VERBOSE);

	auto i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);
	auto imu = new IMU(*i2c);
	imu->init();

	auto display = new Display();
	auto lvgl = new LVGL(*display);

	auto scr = new Scr(*imu);
	scr->start();

	lvgl->start();
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}