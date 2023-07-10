#ifndef CLOCKSTAR_LIBRARY_BATTERY_H
#define CLOCKSTAR_LIBRARY_BATTERY_H

#include <hal/gpio_types.h>
#include "Util/Threaded.h"
#include "Periph/ADC.h"
#include "Util/Hysteresis.h"

class Battery : private Threaded {
public:
	Battery();
	virtual ~Battery();

	uint8_t getLevel() const;
	uint8_t getPercentage() const;
	uint16_t getVoltage() const;
	bool isCharging() const;

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

private:
	static constexpr float MeasureInverval = 100;
	static constexpr uint8_t MeasureCount = 10;

	ADC adc;

	Hysteresis hysteresis;
	//Battery levels will be 0, 1, 2
	static constexpr std::initializer_list<Hysteresis::Threshold> HysteresisThresholds = {{ 15, 25, 1 },
																						  { 65, 75, 2 }};
	uint8_t level = 0;

	uint32_t measureSum = 0;
	uint8_t measureCount = 0;

	uint16_t voltage = 0;
	bool wasCharging = false;

	bool batteryLowAlert = false;
	static constexpr uint8_t LowThresholdPercentage = 5;

	void loop() override;

	void quickSample();

};

#endif //CLOCKSTAR_LIBRARY_SERVICE_H
