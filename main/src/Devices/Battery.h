#ifndef CLOCKSTAR_LIBRARY_BATTERY_H
#define CLOCKSTAR_LIBRARY_BATTERY_H

#include <hal/gpio_types.h>
#include "Util/Threaded.h"
#include "Periph/ADC.h"

class Battery : private Threaded {
public:
	Battery();
	virtual ~Battery();

	uint8_t getLevel() const;
	uint8_t getPercentage() const;
	uint16_t getVoltage() const;
	bool isCharging() const;

	static int16_t getVoltOffset();
	static uint16_t mapReading(uint16_t reading);

private:
	static constexpr float MeasureInverval = 100;
	static constexpr uint8_t MeasureCount = 10;

	ADC adc;

	uint32_t measureSum = 0;
	uint8_t measureCount = 0;

	uint16_t voltage = 0;

	void loop() override;

};

#endif //CLOCKSTAR_LIBRARY_SERVICE_H
