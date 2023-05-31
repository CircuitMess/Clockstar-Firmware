#ifndef CLOCKSTAR_FIRMWARE_IMU_H
#define CLOCKSTAR_FIRMWARE_IMU_H


#include "Drivers/lsm6ds3tr-c_reg.h"
#include "Periph/I2C.h"
#include <cstdint>
#include <functional>
#include "../Util/Threaded.h"
#include <vector>
#include <freertos/semphr.h>
#include <memory>
#include "Util/Queue.h"
#include "../Pins.hpp"


class IMU {
public:
	IMU(I2C& i2c);
	bool init();

	bool getXTilt(float* tilt);
	void onKnock(std::function<void()> func);
	void onStep(std::function<void()> func);
private:
	static constexpr uint8_t Addr = 0x6A;
	I2C& i2c;

	stmdev_ctx_t ctx;
	static int32_t platform_write(void* hndl, uint8_t reg, const uint8_t* data, uint16_t len);
	static int32_t platform_read(void* hndl, uint8_t reg, uint8_t* data, uint16_t len);
	static void delayMillis(uint32_t millis);

//	void printInterruptInfo();

	struct ISRArgs {
		uint32_t pin;
		IMU* imu;

		ISRArgs(uint32_t pin, IMU* imu) : pin(pin), imu(imu){}
	};

	static void IRAM_ATTR gpio_isr_handler(void* arg){
		auto args = (IMU::ISRArgs*) arg;
		auto priority = pdFALSE;
		if(args->pin == IMU_INT1){
			xSemaphoreGiveFromISR(args->imu->sem1, &priority);
		}else if(args->pin == IMU_INT2){
			xSemaphoreGiveFromISR(args->imu->sem2, &priority);
		}
	}


	std::shared_ptr<ISRArgs> isrArgs1, isrArgs2;


	xSemaphoreHandle sem1 = nullptr;
	xSemaphoreHandle sem2 = nullptr;
	ThreadedClosure thread1;
	ThreadedClosure thread2;
	void thread1Func();
	void thread2Func();

	std::function<void()> stepFunc, knockFunc;

};


#endif //CLOCKSTAR_FIRMWARE_IMU_H
