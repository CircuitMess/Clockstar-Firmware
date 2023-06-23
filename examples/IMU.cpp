#include <driver/gpio.h>
#include <nvs_flash.h>
#include "Pins.hpp"
#include "Periph/PinOut.h"
#include "Periph/I2C.h"
#include "Devices/IMU.h"
#include "Fusion/Madgwick.h"
#include "Fusion/Mahony.h"

struct Sample {
	Fusion::Orient rotation; // compared to laying flat on the table
	IMU::Sample imuReading;
};

Queue<Sample>* data;

[[noreturn]] void printer(void* arg){
	int printIndex = 0;
	static constexpr int PrintInterval = 5; // Print every n readings
	static constexpr uint32_t DeltaT = 1000/104; // Time between readings (depends on IMU) [ms]

	for(;;){
		vTaskDelay(DeltaT);

		Sample sample;
		if(!data->get(sample)) continue;

		if(++printIndex < PrintInterval) continue;
		printIndex = 0;

		auto rot = sample.rotation;
		auto raw = sample.imuReading;

		// Uncomment the info you want printed
		printf("P: %+4.0f     Y: %+4.0f     R: %+4.0f\n", rot.pitch, rot.yaw, rot.roll);
		// printf("Gyro: %+7.3f  %+7.3f  %+7.3f     Accel: %+7.3f  %+7.3f  %+7.3f\n", raw.gyroX, raw.gyroY, raw.gyroZ, raw.accelX, raw.accelY, raw.accelZ);
	}
}

[[noreturn]] void reader(void* arg){
	auto imu = (IMU*) arg;

	Fusion::Mahony fusion; // or Madgwick

	for(float i = 0; i < 5000; i++){
		// Laying flat on the table, screen pointing upwards
		fusion.update({ 0, 0, 0, -0.05, 0.05, -0.9 });
	}

	for(;;){
		IMU::Sample reading;
		if(!imu->getNextSample(reading)) continue;

		auto rot = fusion.update(reading);

		Sample sample { rot, reading };
		data->post(sample);
	}
}

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
	bl->off();

	auto i2c = new I2C(I2C_NUM_0, (gpio_num_t) I2C_SDA, (gpio_num_t) I2C_SCL);

	data = new Queue<Sample>(12);

	TaskHandle_t printTask;
	xTaskCreate(printer, "Printer", 4096, nullptr, 5, &printTask);

	auto imu = new IMU(*i2c);
	imu->init();
	imu->enableGyroAccelero(true);

	TaskHandle_t readTask;
	xTaskCreate(reader, "Reader", 4096, imu, 5, &readTask);
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}
