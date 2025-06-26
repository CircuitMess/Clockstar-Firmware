#ifndef CLOCKSTAR_LIBRARY_PINS_HPP
#define CLOCKSTAR_LIBRARY_PINS_HPP

#include <unordered_map>
#include <cstdint>
#include <cstdio>
#include <esp_debug_helpers.h>
#include <vector>

enum class Pin : uint8_t {
	BtnDown,
	BtnUp,
	BtnSelect,
	BtnAlt,
	LedBl,
	Buzz,
	BattRead,
	BattVref,
	Usb,
	I2cSda,
	I2cScl,
	TftSck,
	TftMosi,
	TftDc,
	TftRst,
	Rgb_r,
	Rgb_g,
	Rgb_b,
	Imu_int1,
	Imu_int2,
};

/**
 * Note: This class does not affect pins used in the bootloader hook!
 */
class Pins {
	typedef std::unordered_map<Pin, int> PinMap;
public:
	static int get(Pin pin);

	static void setLatest();

private:
	Pins();

	PinMap* currentMap = nullptr;

	inline static Pins* instance = nullptr;

	void initPinMaps();

	//For original Bit, Bit 2
	PinMap Revision1;

	//For Bit v3
	PinMap Revision2;

	std::vector<PinMap*> pinMaps = { &Revision1, &Revision2 };
};

#endif //CLOCKSTAR_LIBRARY_PINS_HPP
