#ifndef CLOCKSTAR_FIRMWARE_SLEEPLOCK_H
#define CLOCKSTAR_FIRMWARE_SLEEPLOCK_H


#include <esp_pm.h>

class SleepLock {
public:
	SleepLock(esp_pm_lock_type_t type);
	virtual ~SleepLock();

	void acquire();
	void release();

private:
	esp_pm_lock_handle_t lockHndl;
	bool locked = false; // i.e. acquired

};


#endif //CLOCKSTAR_FIRMWARE_SLEEPLOCK_H
