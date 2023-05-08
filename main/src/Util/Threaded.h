#ifndef CLOCKSTAR_FIRMWARE_THREADED_H
#define CLOCKSTAR_FIRMWARE_THREADED_H

#include <cstddef>
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>

class Threaded {
public:
	virtual ~Threaded();

	void start();
	void stop(TickType_t wait = portMAX_DELAY);

protected:
	Threaded(const char* name, size_t stackSize = 12000, uint8_t priority = 5, int8_t core = -1);

	virtual bool onStart();
	virtual void onStop();

	virtual void beforeStop();
	virtual void afterStopSignal();

	virtual void loop() = 0;

private:
	const char* name;
	size_t stackSize;
	const uint8_t priority;
	const int8_t core;

	enum {
		Stopped, Running, Stopping
	} state = Stopped;

	static void threadFunc(void* arg);
	TaskHandle_t task;
	SemaphoreHandle_t stopSem;
	SemaphoreHandle_t stopMut;

};


#endif //CLOCKSTAR_FIRMWARE_THREADED_H