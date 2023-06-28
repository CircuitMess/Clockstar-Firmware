#ifndef CLOCKSTAR_FIRMWARE_TIME_H
#define CLOCKSTAR_FIRMWARE_TIME_H

#include "Util/Threaded.h"
#include "Devices/RTC.h"

class Time : private Threaded {
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

	void loop() override;

};


#endif //CLOCKSTAR_FIRMWARE_TIME_H
