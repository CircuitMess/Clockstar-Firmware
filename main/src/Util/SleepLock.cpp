#include "SleepLock.h"

SleepLock::SleepLock(esp_pm_lock_type_t type){
	ESP_ERROR_CHECK(esp_pm_lock_create(ESP_PM_APB_FREQ_MAX, 0, "Lock", &lockHndl));
}

SleepLock::~SleepLock(){
	if(locked){
		esp_pm_lock_release(lockHndl);
	}
	esp_pm_lock_delete(lockHndl);
}

void SleepLock::acquire(){
	if(locked) return;
	locked = true;
	esp_pm_lock_acquire(lockHndl);
}

void SleepLock::release(){
	if(!locked) return;
	locked = false;
	esp_pm_lock_release(lockHndl);
}
