#include "IMU.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>

IMU::IMU(I2C& i2c) : i2c(i2c){
	ctx = {
			.write_reg = platform_write,
			.read_reg = platform_read,
			.mdelay = delayMillis,
			.handle = this
	};
}

bool IMU::init(){
	uint8_t id;
	lsm6ds3tr_c_device_id_get(&ctx, &id);
	return id == LSM6DS3TR_C_ID;
}

int32_t IMU::platform_write(void* hndl, uint8_t reg, const uint8_t* data, uint16_t len){
	auto imu = (IMU*) hndl;
	return imu->i2c.writeReg(Addr, reg, data, len, 10);
}

int32_t IMU::platform_read(void* hndl, uint8_t reg, uint8_t* data, uint16_t len){
	auto imu = (IMU*) hndl;
	return imu->i2c.readReg(Addr, reg, data, len, 10);
}

void IMU::delayMillis(uint32_t millis){
	vTaskDelay(millis);
}
