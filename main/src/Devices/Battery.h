#ifndef CLOCKSTAR_LIBRARY_BATTERY_H
#define CLOCKSTAR_LIBRARY_BATTERY_H

#include <hal/gpio_types.h>
#include <atomic>
#include "Util/Threaded.h"
#include "Periph/ADC.h"
#include "Util/Hysteresis.h"
#include "Periph/Timer.h"
#include <mutex>

class Battery : private Threaded {
public:
	Battery();
	~Battery() override;

	[[nodiscard]] uint8_t getLevel() const;
	[[nodiscard]] uint8_t getPercentage() const;
	[[nodiscard]] uint16_t getVoltage() const;
	[[nodiscard]] bool isCharging() const;
	[[nodiscard]] bool isCritical() const;

	struct Event {
		enum {
			Charging, BatteryLow
		} action;
		union {
			bool chargeStatus;
		};
	};

	static int16_t getVoltOffset();
	static uint16_t mapReading(uint16_t reading);

	void setLongMeasure(bool enable);

private:
	static constexpr uint32_t ShortMeasureIntverval = 100;
	static constexpr uint32_t LongMeasureIntverval = 6000;
	static constexpr uint8_t MeasureCount = 10;

	ADC adc;

	Hysteresis hysteresis;
	//Battery levels will be 0, 1, 2, 3
	static constexpr std::initializer_list<Hysteresis::Threshold> HysteresisThresholds = { { 4,  12, 1 },
																						   { 15, 25, 2 },
																						   { 65, 75, 3 } };
	uint8_t level = 0;

	uint32_t measureSum = 0;
	uint8_t measureCount = 0;
	void shortMeasureReset();

	bool longMeasure = false;
	std::mutex mut;
	SemaphoreHandle_t sem;
	Timer timer;
	static void isr(void* arg);
	std::atomic_bool abortFlag = false;

	uint16_t voltage = 0;
	bool wasCharging = false;

	bool batteryLowAlert = false;

	void loop() override;

	void quickSample();
	bool longSample();
};

#endif //CLOCKSTAR_LIBRARY_SERVICE_H
