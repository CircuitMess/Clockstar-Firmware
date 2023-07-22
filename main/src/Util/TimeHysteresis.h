#ifndef CLOCKSTAR_FIRMWARE_TIMEHYSTERESIS_H
#define CLOCKSTAR_FIRMWARE_TIMEHYSTERESIS_H

#include <Util/stdafx.h>

template<typename T>
class TimeHysteresis {
public:
	TimeHysteresis(const uint32_t holdTime, const T initialVal = T()) : holdTime(holdTime), val(initialVal){}

	T update(T newVal){
		uint32_t now = millis();

		if(pendingTime == 0 || pendingVal != newVal){
			pendingVal = newVal;
			pendingTime = now;
			return val;
		}

		uint32_t elapsed = now - pendingTime;
		if(elapsed > holdTime){
			val = pendingVal;
			pendingTime = 0;
		}

		return val;
	}

	void reset(T newVal){
		val = newVal;
		pendingTime = 0;
	}

	T get() const{
		return val;
	}

private:
	const uint32_t holdTime;

	T val;

	T pendingVal;
	uint32_t pendingTime = 0;

};


#endif //CLOCKSTAR_FIRMWARE_TIMEHYSTERESIS_H
