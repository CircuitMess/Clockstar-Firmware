#ifndef CLOCKSTAR_FIRMWARE_IMU_H
#define CLOCKSTAR_FIRMWARE_IMU_H

#include "Drivers/lsm6ds3tr-c_reg.h"
#include "Periph/I2C.h"
#include <cstdint>
#include "Util/Threaded.h"
#include <vector>
#include <freertos/semphr.h>
#include <memory>
#include "Pins.hpp"
#include "Util/Events.h"
#include "Util/Queue.h"
#include <mutex>


/**
 * Axis orientation when the watch is on your left wrist:
 * 		X - direction of your fingers
 * 		Y - towards the lower edge of the device
 * 		Z - into the screen
 */

class IMU {
public:
	IMU(I2C& i2c);
	bool init();

	struct GyroAcceleroRaw {
		int16_t gyroX;
		int16_t gyroY;
		int16_t gyroZ;
		int16_t acceleroX;
		int16_t acceleroY;
		int16_t acceleroZ;
	};

	enum class TiltDirection {
		Lifted, Lowered
	};
	enum class HandSide {
		Left, Right
	};
	enum class WatchPosition {
		FaceUp, FaceDown
	};

	/**
	 * Sets the watch wear position for tilt detection. Default is face-up.
	 * @param wristPosition Face-up or face-down position
	 */
	void setWristPosition(WatchPosition wristPosition);

	/**
	 * Sets the tilt direction that should trigger tilt detection. Default is lifted.
	 * @param direction Lifting it towards you or lowering it away from you
	 */
	void setTiltDirection(TiltDirection direction);

	/**
	 * Enable/Disable significant motion detection events. OFF by default
	 * @param enable
	 */
	void enableMotionDetection(bool enable);

	[[nodiscard]] Queue<GyroAcceleroRaw>& getRawReads();
	void enableGyroAccelero(bool enable);

	struct Orientation{
		float roll;
		float pitch;
		float yaw;
	};
	Orientation getOrientation();

private:
	static constexpr uint8_t Addr = 0x6A;
	I2C& i2c;

	stmdev_ctx_t ctx;
	static int32_t platform_write(void* hndl, uint8_t reg, const uint8_t* data, uint16_t len);
	static int32_t platform_read(void* hndl, uint8_t reg, uint8_t* data, uint16_t len);
	static void delayMillis(uint32_t millis);

	static constexpr uint16_t ReadingsWatermark = 200;
	static constexpr size_t MaxReads = 250;
	Queue<GyroAcceleroRaw> rawReads;
	void clearFifo();

	TiltDirection tiltDirection = TiltDirection::Lifted;
	HandSide handSide = HandSide::Left;
	WatchPosition position = WatchPosition::FaceUp;
	static constexpr uint8_t SignificantMotionSens = 4;

	void printInterruptInfo();

	struct ISRArgs {
		uint32_t pin;
		IMU* imu;

		ISRArgs(uint32_t pin, IMU* imu) : pin(pin), imu(imu){}
	};

	std::shared_ptr<ISRArgs> isrArgs1, isrArgs2;

	static void IRAM_ATTR gpio_isr_handler(void* arg){
		auto args = (IMU::ISRArgs*) arg;
		auto priority = pdFALSE;
		if(args->pin == IMU_INT1){
			xSemaphoreGiveFromISR(args->imu->sem1, &priority);
		}else if(args->pin == IMU_INT2){
			xSemaphoreGiveFromISR(args->imu->sem2, &priority);
		}
	}


	xSemaphoreHandle sem1 = nullptr;
	xSemaphoreHandle sem2 = nullptr;
	ThreadedClosure thread1;
	ThreadedClosure thread2;
	void thread1Func();
	void thread2Func();

	Orientation orientation{};
	ThreadedClosure fusionThread;
	void fusionThreadFunc();
	std::mutex fusionMutex;
};


#endif //CLOCKSTAR_FIRMWARE_IMU_H
