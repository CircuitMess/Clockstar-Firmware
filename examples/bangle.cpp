#include <driver/gpio.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include "Periph/Bluetooth.h"
#include "BLE/GAP.h"
#include "BLE/Server.h"
#include "Notifs/Bangle.h"

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
	// esp_log_level_set("BLE::Server", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::Server::Service", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::Server::Char", ESP_LOG_VERBOSE);
	// esp_log_level_set("BLE::Server::CharInfo", ESP_LOG_VERBOSE);
	esp_log_level_set("Bangle", ESP_LOG_VERBOSE);

	auto bt = new Bluetooth();
	auto gap = new BLE::GAP();
	auto server = new BLE::Server(gap);

	auto bangle = new Bangle(server);

	bangle->setOnConnect([](){
		printf("Gadgetbridge connected\n");
	});

	bangle->setOnDisconnect([](){
		printf("Gadgetbridge disconnected\n");
	});

	auto print = [](const Notif& notif){
		printf("App ID: %s\n", notif.appID.c_str());
		printf("Title: %s\n", notif.title.c_str());
		printf("Subtitle: %s\n", notif.subtitle.c_str());
		printf("Message: %s\n", notif.message.c_str());
		printf("Pos: %s / Neg: %s\n", notif.label.pos.c_str(), notif.label.neg.c_str());
		printf("\n");
	};

	bangle->setOnNotifAdd([print](Notif notif){
		printf("Add 0x%lx\n", notif.uid);
		print(notif);
	});

	bangle->setOnNotifModify([print](Notif notif){
		printf("Modify 0x%lx\n", notif.uid);
		print(notif);
	});

	bangle->setOnNotifRemove([](uint32_t uid){
		printf("Removing 0x%lx\n", uid);
	});

	server->start();
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}