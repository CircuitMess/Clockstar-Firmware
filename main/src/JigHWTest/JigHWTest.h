#ifndef JIGHWTEST_H
#define JIGHWTEST_H

#include <cstdint>
#include <string>
#include <vector>
#include "Periph/I2C.h"
#include "Devices/IMU.h"
#include "Devices/RTC.h"

struct Test {
	bool (* test)();
	const char* name;
};

class JigHWTest {
public:
	JigHWTest(I2C& i2c);
	void start();

private:
	// Sprite *canvas;
	// Display *display;

	I2C& i2c;
	IMU* imu;
	RTC* rtc;

	static JigHWTest* test;
	std::vector<Test> tests;
	const char* currentTest;

	void log(const char* property, const char* value);
	void log(const char* property, float value);
	void log(const char* property, double value);
	void log(const char* property, bool value);
	void log(const char* property, uint32_t value);
	void log(const char* property, int32_t value);
	void log(const char* property, const std::string& value);

	static bool RTCTest();
	static bool Time();
	static bool Gyro();

	static const int16_t referenceVoltage = 4000;
};

#endif //JIGHWTEST_H
