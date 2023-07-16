#ifndef CLOCKSTAR_FIRMWARE_TIME_H
#define CLOCKSTAR_FIRMWARE_TIME_H

#include "Util/Threaded.h"
#include "Devices/RTC.h"

class Time : public SleepyThreaded {
public:
	Time(RTC& rtc);
	~Time();

	struct Event {
		enum { Updated } action;
		union {
			struct {
				tm time;
			} updated;
		};
	};

	tm getTime() const;
	void setTime(tm time_tm);
	void setTime(time_t time);

private:
	RTC& rtc;

	static constexpr uint32_t UpdateInterval = 5000; // [ms]
	uint64_t updateTime = 0;

	time_t time;

	void sleepyLoop() override;
	tm updateFromRTC();

	// Hide public functions
	using Threaded::start;
	using Threaded::stop;

};


#endif //CLOCKSTAR_FIRMWARE_TIME_H
