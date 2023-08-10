#ifndef BIT_FIRMWARE_COLOR_H
#define BIT_FIRMWARE_COLOR_H

#include <cstdint>

typedef uint16_t Color;

struct Pixel {
	uint8_t r, g, b;

	bool operator==(const Pixel& right) const{
		return r == right.r && g == right.g && b == right.b;
	}
};

Color C_RGB(uint8_t r, uint8_t g, uint8_t b);

Color C_HEX(uint32_t hex);
#endif //BIT_FIRMWARE_COLOR_H
