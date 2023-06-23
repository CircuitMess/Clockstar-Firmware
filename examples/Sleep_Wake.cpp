#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>
#include <nvs_flash.h>
#include <esp_log.h>
#include <esp_sleep.h>
#include <memory>
#include <Periph/I2C.h>
#include <Devices/IMU.h>
#include <Devices/Input.h>
#include "Util/Events.h"
#include "Pins.hpp"
#include "Devices/Display.h"
#include "LV_Interface/LVGL.h"
#include "LV_Interface/LVScreen.h"

/**
 * Puts the ESP to light sleep, and wakes it on any button press or IMU interrupt.
 */

void sleep(){
	printf("Going to sleep...\n");
	printf("INT2 is %d\n", gpio_get_level((gpio_num_t) IMU_INT2));
	vTaskDelay(100);
	esp_light_sleep_start();
	printf("Awake!\n");
}

[[noreturn]] void btnProcess(void* arg){
	EventQueue events(12);
	Events::listen(Facility::Input, &events);
	Events::listen(Facility::Motion, &events);

	Event evt;
	for(;;){
		if(events.get(evt, portMAX_DELAY) == false) continue;
		if(evt.facility == Facility::Motion){
			std::unique_ptr<IMU::Event> data((IMU::Event*) evt.data);
			if(data->action == IMU::Event::WristTilt){
				printf("Wrist tilt\n");
			}

			sleep();
		}else if(evt.facility == Facility::Input){
			std::unique_ptr<Input::Data> data((Input::Data*) evt.data);
			if(data->action != Input::Data::Press) continue;

			printf("Pressed %s\n", Input::PinLabels.at(data->btn));

			sleep();
		}
	}
}

// Screen with a moving button, simply to demonstrate the display is still working after wake.
class Scr : public LVScreen {
public:
	Scr(){
		btn = lv_btn_create(obj);
		lv_obj_set_style_bg_color(btn, lv_color_make(150, 150, 150), 0);
		lv_obj_set_style_bg_opa(btn, LV_OPA_COVER, 0);
	}

private:
	lv_obj_t* btn;
	int x = 0;
	int dir = 1;

	void loop() override{
		if(x > 100 || x < 0) dir *= -1;
		x += dir;
		lv_obj_set_pos(btn, x, 10);
	}
};

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

	esp_log_level_set("*", ESP_LOG_WARN);

	auto input = new Input();
	TaskHandle_t procTask;
	xTaskCreatePinnedToCore(btnProcess, "Process", 12 * 1024, nullptr, 5, &procTask, 0);

	auto i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);
	auto imu = new IMU(*i2c);
	imu->init();
	imu->enableMotionDetection(true);
	imu->setWristPosition(IMU::WatchPosition::FaceUp);
	imu->setTiltDirection(IMU::TiltDirection::Lifted);

	esp_sleep_enable_gpio_wakeup();
	gpio_wakeup_enable((gpio_num_t) BTN_UP, GPIO_INTR_HIGH_LEVEL);
	gpio_wakeup_enable((gpio_num_t) BTN_DOWN, GPIO_INTR_HIGH_LEVEL);
	gpio_wakeup_enable((gpio_num_t) BTN_SELECT, GPIO_INTR_HIGH_LEVEL);
	gpio_wakeup_enable((gpio_num_t) BTN_ALT, GPIO_INTR_HIGH_LEVEL);
	gpio_wakeup_enable((gpio_num_t) IMU_INT2, GPIO_INTR_HIGH_LEVEL);

	auto display = new Display();
	auto lvgl = new LVGL(*display);

	auto scr = new Scr();
	scr->start();

	lvgl->start();

	vTaskDelay(1000);
	sleep();
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}