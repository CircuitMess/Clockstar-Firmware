#include <driver/gpio.h>
#include <nvs_flash.h>
#include "Pins.hpp"
#include "Periph/I2C.h"
#include "Periph/PinOut.h"
#include "Periph/Bluetooth.h"
#include "Devices/Display.h"
#include "Devices/Input.h"
#include "Devices/IMU.h"
#include "BLE/GAP.h"
#include "BLE/Client.h"
#include "BLE/Server.h"
#include "Notifs/Phone.h"
#include "LV_Interface/LVGL.h"
#include "LV_Interface/FSLVGL.h"
#include "LV_Interface/InputLVGL.h"
#include "Util/Services.h"
#include "Services/Time.h"
#include <lvgl/lvgl.h>
#include "Theme/theme.h"
#include "Screens/Lock/LockScreen.h"
#include "Devices/Battery.h"

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

	auto i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);
	auto rtc = new RTC(*i2c);
	auto imu = new IMU(*i2c);

	auto time = new Time(*rtc);
	Services.set(Service::Time, time); // Time service is required as soon as Phone is up

	auto bt = new Bluetooth();
	auto gap = new BLE::GAP();
	auto client = new BLE::Client(gap);
	auto server = new BLE::Server(gap);
	auto phone = new Phone(server, client);
	server->start();

	auto battery = new Battery();

	Services.set(Service::Battery, battery);
	Services.set(Service::IMU, imu);
	Services.set(Service::Phone, phone);

	auto disp = new Display();
	auto input = new Input();

	auto lvgl = new LVGL(*disp);
	auto theme = theme_init(lvgl->disp());
	lv_disp_set_theme(lvgl->disp(), theme);

	auto lvglInput = new InputLVGL();
	auto fs = new FSLVGL('S');
	fs->addToCache("/bg.bin");

	// Load start screen here
	auto scr = new LockScreen();
	scr->start();

	// Start UI thread after initialization
	lvgl->start();

}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
