#ifndef CLOCKSTAR_LIBRARY_BATTERY_H
#define CLOCKSTAR_LIBRARY_BATTERY_H

#include <hal/gpio_types.h>
#include <atomic>
#include "Util/Threaded.h"
#include "Periph/ADC.h"
#include "Util/Hysteresis.h"
#include "Periph/Timer.h"
#include "Util/TimeHysteresis.h"
#include <mutex>

class Battery : private Threaded {
public:
	Battery();
	~Battery() override;

	enum Level { Critical = 0, VeryLow, Low, Mid, Full, COUNT };

	void setSleep(bool sleep);

	uint8_t getPerc() const;
	Level getLevel() const;
	bool isCharging() const;

	struct Event {
		enum {
			Charging, LevelChange
		} action;
		union {
			bool chargeStatus;
			Level level;
		};
	};

	static int16_t getVoltOffset();
	static uint16_t mapRawReading(uint16_t reading);

private:
	static constexpr uint32_t ShortMeasureIntverval = 100;
	static constexpr uint32_t LongMeasureIntverval = 6000;

	ADC adc;

	Hysteresis hysteresis;

	std::mutex mut;

	TimeHysteresis<bool> chargeHyst;
	bool wasCharging = false;
	bool sleep = false;

	std::atomic_bool abortFlag = false;

	SemaphoreHandle_t sem;
	Timer timer;
	static void isr(void* arg);
	void loop() override;

	void checkCharging();
	void sample(bool fresh = false);
	void startTimer();

};

#endif //CLOCKSTAR_LIBRARY_SERVICE_H
