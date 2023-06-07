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
#include <esp_spiffs.h>
#include <esp_log.h>
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

	auto ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	auto bl = new PinOut(PIN_BL, true);
	bl->on();

	auto i2c = new I2C(0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);

	auto bt = new Bluetooth();
	auto gap = new BLE::GAP();
	auto client = new BLE::Client(gap);

	auto disp = new Display();
	auto lvgl = new LVGL(*disp);

	// Load start screen here
	auto scr = lv_obj_create(nullptr);
	lv_scr_load(scr);

	//init spiffs
	esp_vfs_spiffs_conf_t conf = {
			.base_path = "/spiffs",
			.partition_label = NULL,
			.max_files = 5,
			.format_if_mount_failed = false
	};
	ret = esp_vfs_spiffs_register(&conf);
	const char* TAG = "spiffs";
	if(ret != ESP_OK){
		if(ret == ESP_FAIL){
			ESP_LOGE(TAG, "Failed to mount or format filesystem");
		}else if(ret == ESP_ERR_NOT_FOUND){
			ESP_LOGE(TAG, "Failed to find SPIFFS partition");
		}else{
			ESP_LOGE(TAG, "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
		}
		return;
	}

	// Start UI thread after initialization
	lvgl->start();
}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
