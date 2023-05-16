#include "Bluetooth.h"
#include <esp_bt.h>
#include <esp_bt_main.h>

Bluetooth::Bluetooth(){
	esp_bt_controller_config_t bt_cfg = BT_CONTROLLER_INIT_CONFIG_DEFAULT();
	ESP_ERROR_CHECK(esp_bt_controller_init(&bt_cfg));
	ESP_ERROR_CHECK(esp_bt_controller_enable(ESP_BT_MODE_BLE));

	ESP_ERROR_CHECK(esp_bluedroid_init());
	ESP_ERROR_CHECK(esp_bluedroid_enable());
}

Bluetooth::~Bluetooth(){
	esp_bluedroid_disable();
	esp_bluedroid_deinit();

	esp_bt_controller_disable();
	esp_bt_controller_deinit();
	esp_bt_controller_mem_release(ESP_BT_MODE_BLE);
}
