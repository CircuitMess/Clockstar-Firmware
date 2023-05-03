#ifndef CLOCKSTAR_FIRMWARE_RTC_H
#define CLOCKSTAR_FIRMWARE_RTC_H

#include "Periph/I2C.h"
#include <ctime>

class RTC {
public:
	RTC(I2C& i2C);
	bool init();

	tm getTime();
	void setTime(const tm& time);

private:
	I2C& i2c;
	static constexpr uint8_t Addr = 0x51;

	uint8_t bcd2dec(uint8_t bcd);
	uint8_t dec2bcd(uint8_t dec);

};

#endif //CLOCKSTAR_FIRMWARE_RTC_H
