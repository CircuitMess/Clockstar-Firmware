#ifndef CLOCKSTAR_FIRMWARE_QUEUE_H
#define CLOCKSTAR_FIRMWARE_QUEUE_H

#include <cstddef>
#include <freertos/FreeRTOS.h>
#include <freertos/portmacro.h>
#include <freertos/queue.h>
#include <memory>

template<typename T>
class Queue {
public:
	Queue(size_t count){
		queue = xQueueCreate(count, sizeof(T));
	}

	virtual ~Queue(){
		vQueueDelete(queue);
	}

	bool get(T& item, TickType_t timeout = portMAX_DELAY){
		return xQueueReceive(queue, &item, timeout) == pdTRUE;
	}

	bool post(T& item, TickType_t timeout = portMAX_DELAY){
		return xQueueSend(queue, &item, timeout) == pdTRUE;
	}

	void reset(){
		xQueueReset(queue);
	}

private:
	QueueHandle_t queue;

};

template<typename T>
class PtrQueue {
public:
	PtrQueue(size_t size) : size(size){
		queue = xQueueCreate(size, sizeof(T*));
	}

	virtual ~PtrQueue(){
		vQueueDelete(queue);
	}

	std::unique_ptr<T> get(TickType_t timeout = portMAX_DELAY){
		T* ptr;
		if(xQueueReceive(queue, &ptr, timeout) != pdTRUE) return nullptr;
		return std::unique_ptr<T>(ptr);
	}

	std::unique_ptr<T> post(std::unique_ptr<T> item, TickType_t timeout = portMAX_DELAY){
		T* ptr = item.release();
		if(xQueueSend(queue, &ptr, timeout) == pdTRUE){
			ptr = nullptr;
		}
		return std::unique_ptr<T>(ptr);
	}

	void reset(){
		xQueueReset(queue);
	}

	const size_t size;

private:
	QueueHandle_t queue;

};

#endif //CLOCKSTAR_FIRMWARE_QUEUE_H
