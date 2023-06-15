#ifndef CLOCKSTAR_FIRMWARE_IMU_H
#define CLOCKSTAR_FIRMWARE_IMU_H

#include "Drivers/lsm6ds3tr-c_reg.h"
#include "Periph/I2C.h"
#include "Util/Threaded.h"
#include "Util/Queue.h"
#include <cstdint>
#include <vector>
#include <memory>

/**
 * Axis orientation when the watch is on your left wrist:
 * 		X - direction of your fingers
 * 		Y - towards the lower edge of the device
 * 		Z - into the screen
 */

class IMU {
public:
	IMU(I2C& i2c);
	virtual ~IMU();

	bool init();

	struct Event {
		enum { SignMotion, DoubleTap, SingleTap, WristTilt, FIFO } action;
	};

	struct Sample {
		uint16_t gyroX;
		uint16_t gyroY;
		uint16_t gyroZ;
		uint16_t acceleroX;
		uint16_t acceleroY;
		uint16_t acceleroZ;
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

	bool getNextSample(Sample& sample, TickType_t wait);
	void enableGyroAccelero(bool enable);

private:
	static constexpr uint8_t Addr = 0x6A;
	I2C& i2c;

	static int32_t platform_write(void* hndl, uint8_t reg, const uint8_t* data, uint16_t len);
	static int32_t platform_read(void* hndl, uint8_t reg, uint8_t* data, uint16_t len);
	stmdev_ctx_t ctx = {
			.write_reg = platform_write,
			.read_reg = platform_read,
			.mdelay = vTaskDelay,
			.handle = this
	};

	static constexpr uint16_t ReadingsWatermark = 200;
	static constexpr size_t MaxReads = 250;
	Queue<Sample> fifoSamples;
	void clearFifo();

	TiltDirection tiltDirection = TiltDirection::Lifted;
	HandSide handSide = HandSide::Left;
	WatchPosition position = WatchPosition::FaceUp;
	static constexpr uint8_t SignificantMotionSens = 4;

	void printInterruptInfo();

	SemaphoreHandle_t sem1 = nullptr;
	SemaphoreHandle_t sem2 = nullptr;
	static void IRAM_ATTR isr1(void* arg);
	static void IRAM_ATTR isr2(void* arg);
	ThreadedClosure thread1;
	ThreadedClosure thread2;
	[[noreturn]] void thread1Func();
	[[noreturn]] void thread2Func();
};


#endif //CLOCKSTAR_FIRMWARE_IMU_H
