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
#include "Services/ChirpSystem.h"
#include "Settings/Settings.h"
#include "Services/SleepMan.h"
#include "UIElements/ClockLabelBig.h"
#include "Devices/Battery.h"
#include "Services/BacklightBrightness.h"
#include "Services/StatusCenter.h"
#include "Util/Notes.h"

void init(){
	gpio_install_isr_service(ESP_INTR_FLAG_LOWMED | ESP_INTR_FLAG_SHARED | ESP_INTR_FLAG_IRAM);

	auto battery = new Battery();
	Services.set(Service::Battery, battery);
	// TODO: turn off if battery critical

	auto blPwm = new PWM(PIN_BL, LEDC_CHANNEL_1, true);
	blPwm->detach();
	auto bl = new BacklightBrightness(blPwm);
	Services.set(Service::Backlight, bl);

	auto ret = nvs_flash_init();
	if(ret == ESP_ERR_NVS_NO_FREE_PAGES || ret == ESP_ERR_NVS_NEW_VERSION_FOUND){
		ESP_ERROR_CHECK(nvs_flash_erase());
		ret = nvs_flash_init();
	}
	ESP_ERROR_CHECK(ret);

	auto settings = new Settings();
	Services.set(Service::Settings, settings);

	auto i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);
	auto rtc = new RTC(*i2c);

	auto imu = new IMU(*i2c);
	Services.set(Service::IMU, imu);

	auto time = new Time(*rtc);
	Services.set(Service::Time, time); // Time service is required as soon as Phone is up

	auto bt = new Bluetooth();
	auto gap = new BLE::GAP();
	auto client = new BLE::Client(gap);
	auto server = new BLE::Server(gap);
	auto phone = new Phone(server, client);
	server->start();
	Services.set(Service::Phone, phone);

	auto buzzPwm = new PWM(PIN_BUZZ, LEDC_CHANNEL_0);
	auto audio = new ChirpSystem(*buzzPwm);
	Services.set(Service::Audio, audio);

	auto status = new StatusCenter();
	Services.set(Service::Status, status);

	auto disp = new Display();
	auto input = new Input();
	Services.set(Service::Input, input);

	auto lvgl = new LVGL(*disp);
	auto theme = theme_init(lvgl->disp());
	lv_disp_set_theme(lvgl->disp(), theme);

	auto sleep = new SleepMan(*lvgl);
	Services.set(Service::Sleep, sleep);
	//TODO - apply sleepTime from Settings

	auto lvglInput = new InputLVGL();
	auto fs = new FSLVGL('S');
	FSLVGL::loadCache();

	if(settings->get().notificationSounds){
		audio->play({
							Chirp{ .startFreq = NOTE_E4, .endFreq = NOTE_GS4, .duration = 100 },
							Chirp{ .startFreq = 0, .endFreq = 0, .duration = 200 },
							Chirp{ .startFreq = NOTE_GS4, .endFreq = NOTE_B4, .duration = 100 },
							Chirp{ .startFreq = 0, .endFreq = 0, .duration = 200 },
							Chirp{ .startFreq = NOTE_B4, .endFreq = NOTE_E5, .duration = 100 }
					});
	}

	// Load start screen here
	lvgl->startScreen([](){ return std::make_unique<LockScreen>(); });

	// Start UI thread after initialization
	lvgl->start();

	bl->fadeIn();
}

extern "C" void app_main(void){
	init();

	vTaskDelete(nullptr);
}
