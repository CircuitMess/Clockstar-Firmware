#ifndef CLOCKSTAR_FIRMWARE_STDAFX_H
#define CLOCKSTAR_FIRMWARE_STDAFX_H

#include <cstdint>
#include <utility>

template<typename T>
T map(T val, decltype(val) fromLow, decltype(val) fromHigh, decltype(val) toLow, decltype(val) toHigh){
	if(fromLow > fromHigh){
		std::swap(fromLow, fromHigh);
	}

	if(toLow > toHigh){
		std::swap(toLow, toHigh);
	}

	return (val - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}

uint32_t millis();
uint32_t micros();

#endif //CLOCKSTAR_FIRMWARE_STDAFX_H
