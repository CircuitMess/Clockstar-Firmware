#ifndef CLOCKSTAR_FIRMWARE_IMU_H
#define CLOCKSTAR_FIRMWARE_IMU_H


#include "Drivers/lsm6ds3tr-c_reg.h"
#include "Periph/I2C.h"
#include <cstdint>

class IMU {
public:
	IMU(I2C& i2c);
	bool init();

private:
	static constexpr uint8_t Addr = 0x6A;
	I2C& i2c;

	stmdev_ctx_t ctx;
	static int32_t platform_write(void* hndl, uint8_t reg, const uint8_t* data, uint16_t len);
	static int32_t platform_read(void* hndl, uint8_t reg, uint8_t* data, uint16_t len);
	static void delayMillis(uint32_t millis);

};


#endif //CLOCKSTAR_FIRMWARE_IMU_H
