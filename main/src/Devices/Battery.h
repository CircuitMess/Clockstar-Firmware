#ifndef CLOCKSTAR_LIBRARY_BATTERY_H
#define CLOCKSTAR_LIBRARY_BATTERY_H

#include <atomic>
#include "Util/Threaded.h"
#include "Periph/ADC.h"
#include "Periph/Timer.h"
#include "Util/TimeHysteresis.h"
#include <mutex>
#include <memory>

class Battery : public Threaded {
public:
	Battery();
	virtual ~Battery() override;
	void begin();

	enum Level { Critical = 0, VeryLow, Low, Mid, Full, COUNT };
	enum class ChargingState : uint8_t { Unplugged, Charging, Full };

	virtual uint8_t getPerc() const = 0;
	virtual Level getLevel() const = 0;
	ChargingState getChargingState() const;

	struct Event {
		enum {
			Charging, LevelChange
		} action;
		union {
			ChargingState chargeStatus;
			Level level;
		};
	};

	bool isShutdown() const;
	void setShutdown(bool value) { shutdown = value; }

	void setSleep(bool sleep);
	void startTimer();

protected:
	void loop() override;

	void checkCharging(bool fresh = false);

	virtual void sample(bool fresh = false) = 0;
	virtual void onSleep(bool sleep) {}

private:
	static constexpr uint32_t ShortMeasureIntverval = 100;
	static constexpr uint32_t LongMeasureIntverval = 6000;

	std::mutex mut;

	TimeHysteresis<ChargingState> chargeHyst;
	ChargingState lastCharging = ChargingState::Unplugged;
	bool sleep = false;

	std::atomic_bool abortFlag = false;

	SemaphoreHandle_t sem;
	Timer timer;
	static void isr(void* arg);

	bool shutdown = false;

	/**
	 * Sometimes ADC will start having an offset during sleep and after wakeup.
	 * This method will be called every time the Battery class wakes up during sleep,
	 * and also after final wakeup of the rest of the system.
	 *
	 * Necessary on certain HW revisions because of this ADC reading glitch after/during light sleep
	 * (https://github.com/espressif/esp-idf/issues/12612)
	 */
	virtual void inSleepReconfigure() = 0;
};

#endif //CLOCKSTAR_LIBRARY_BATTERY_H
