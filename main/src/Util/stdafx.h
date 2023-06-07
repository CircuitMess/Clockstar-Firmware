#ifndef CLOCKSTAR_FIRMWARE_STDAFX_H
#define CLOCKSTAR_FIRMWARE_STDAFX_H

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

#endif //CLOCKSTAR_FIRMWARE_STDAFX_H
