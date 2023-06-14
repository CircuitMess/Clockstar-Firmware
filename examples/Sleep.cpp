#include <driver/gpio.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include <esp_sleep.h>
#include "Periph/Bluetooth.h"
#include "BLE/GAP.h"
#include "BLE/Server.h"
#include <esp_pm.h>
#include "Pins.hpp"

/**
 * Exactly the same as the GATT Server example, with added auto sleep. Server parameters should be updated - src/BLE/Server.cpp:198
 */

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

	gpio_set_direction((gpio_num_t) PIN_BL, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t) PIN_BL, 1);

	esp_log_level_set("*", ESP_LOG_WARN);
	esp_log_level_set("clk", ESP_LOG_DEBUG);
	esp_log_level_set("BLE", ESP_LOG_VERBOSE);
	esp_log_level_set("BLE::Server", ESP_LOG_VERBOSE);
	esp_log_level_set("BLE::Server::Service", ESP_LOG_VERBOSE);
	esp_log_level_set("BLE::Server::Char", ESP_LOG_VERBOSE);
	esp_log_level_set("BLE::Server::CharInfo", ESP_LOG_VERBOSE);

	esp_pm_config_t pm_config = {
			.max_freq_mhz = 240, // e.g. 80, 160, 240
			.min_freq_mhz = 240, // e.g. 40
			.light_sleep_enable = false // enable light sleep
	};
	ESP_ERROR_CHECK(esp_pm_configure(&pm_config));
	esp_sleep_enable_bt_wakeup();

	auto bt = new Bluetooth();
	auto gap = new BLE::GAP();
	auto server = new BLE::Server(gap);

	static constexpr esp_bt_uuid_t ServiceUID = {
			.len = ESP_UUID_LEN_128,
			.uuid = { .uuid128 = { 0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x01, 0x00, 0x40, 0x6E }}
	};

	// Server-side RX and TX
	static constexpr esp_bt_uuid_t RxCharUID = {
			.len = ESP_UUID_LEN_128,
			.uuid = { .uuid128 = { 0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x02, 0x00, 0x40, 0x6E }}
	};static constexpr esp_bt_uuid_t TxCharUID = {
			.len = ESP_UUID_LEN_128,
			.uuid = { .uuid128 = { 0x9E, 0xCA, 0xDC, 0x24, 0x0E, 0xE5, 0xA9, 0xE0, 0x93, 0xF3, 0xA3, 0xB5, 0x03, 0x00, 0x40, 0x6E }}
	};

	auto service = server->addService(ServiceUID);
	auto txChar = service->addChar(TxCharUID, ESP_GATT_CHAR_PROP_BIT_NOTIFY);
	auto rxChar = service->addChar(RxCharUID, ESP_GATT_CHAR_PROP_BIT_WRITE);

	server->start();

	std::vector<uint8_t> data;
	for(;;){
		auto msg = rxChar->getNextWrite();
		if(msg == nullptr) continue;

		data.insert(data.end(), msg->data.cbegin(), msg->data.cend());
		msg->data.push_back(0);
		printf("Received: %s\n", msg->data.data());
		msg->data.pop_back();

		auto nl = std::find(data.begin(), data.end(), '\n');
		if(nl != data.end()){
			std::vector forSend(data.begin(), nl+1);
			data.erase(data.begin(), nl+1);
			txChar->sendNotif(forSend);

			forSend.push_back(0);
			printf("Sending: %s", forSend.data());
		}
	}

	pm_config.light_sleep_enable = true;
	ESP_ERROR_CHECK(esp_pm_configure(&pm_config));
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}