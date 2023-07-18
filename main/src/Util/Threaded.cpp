#include "Threaded.h"
#include "stdafx.h"
#include <esp_log.h>

Threaded::Threaded(const char* name, size_t stackSize, uint8_t priority, int8_t core) : name(name), stackSize(stackSize), priority(priority), core(core){
	stopSem = xSemaphoreCreateBinary();
	stopMut = xSemaphoreCreateMutex();
}

Threaded::~Threaded(){
	if(state != Stopped){
		ESP_LOGE("Threaded", "Threaded %s destructing while still running", name);
		abort();
	}

	vSemaphoreDelete(stopSem);
	vSemaphoreDelete(stopMut);
}

void Threaded::start(){
	if(state != Stopped) return;

	if(!onStart()) return;

	state = Running;

	if(core == -1){
		xTaskCreate(Threaded::threadFunc, name, stackSize, this, priority, &task);
	}else{
		xTaskCreatePinnedToCore(Threaded::threadFunc, name, stackSize, this, priority, &task, core);
	}
}

void Threaded::stop(TickType_t wait){
	if(xSemaphoreTake(stopMut, wait) == pdFALSE) return;

	if(state != Running){
		xSemaphoreGive(stopMut);
		return;
	}

	beforeStop();
	state = Stopping;
	afterStopSignal();

	xSemaphoreTake(stopSem, wait);

	xSemaphoreGive(stopMut);
}

void Threaded::threadFunc(void* arg){
	auto thr = static_cast<Threaded*>(arg);

	while(thr->state == Running){
		thr->loop();
	}

	thr->onStop();

	thr->state = Stopped;
	xSemaphoreGive(thr->stopSem);

	vTaskDelete(nullptr);
}

bool Threaded::onStart(){
	return true;
}

void Threaded::onStop(){ }

void Threaded::beforeStop(){ }

void Threaded::afterStopSignal(){ }

bool Threaded::running(){
	return state == Running || state == Stopping;
}

ThreadedClosure::ThreadedClosure(Lambda loopFn, const char* name, size_t stackSize, uint8_t priority, int8_t core) : Threaded(name, stackSize, priority, core), fn(std::move(loopFn)){}

void ThreadedClosure::loop(){
	fn();
}

SleepyThreaded::SleepyThreaded(TickType_t loopInterval, const char* name, size_t stackSize, uint8_t priority, int8_t core) : Threaded(name, stackSize, priority, core), SleepTime(loopInterval){
	pauseSem = xSemaphoreCreateBinary();
}

SleepyThreaded::~SleepyThreaded(){
	vSemaphoreDelete(pauseSem);
}

void SleepyThreaded::pause(){
	if(paused) return;
	xSemaphoreGive(pauseSem);
	while(!paused){
		vTaskDelay(1);
	}
}

void SleepyThreaded::resume(){
	paused = false;
	start();
}

void SleepyThreaded::resetTime(){
	lastLoop = millis();
}

void SleepyThreaded::loop(){
	if(millis() - lastLoop < SleepTime){
		if(xSemaphoreTake(pauseSem, millis() - lastLoop + 1) == pdTRUE){
			stop(0);
			paused = true;
			return;
		}
		return;
	}

	resetTime();
	sleepyLoop();
}
