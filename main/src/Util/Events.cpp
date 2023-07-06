#include "Events.h"
#include <cstring>

std::unordered_map<Facility, std::unordered_set<EventQueue*>> Events::queues;

void Events::listen(Facility facility, EventQueue* queue){
	queues[facility].insert(queue);
}

void Events::unlisten(EventQueue* queue){
	for(auto& pair : queues){
		pair.second.erase(queue);
	}
}

void Events::post(Facility facility, const void* data, size_t size){
	auto pair = queues.find(facility);
	if(pair == queues.end()) return;

	for(auto& queue: pair->second){
		void* qData = nullptr;
		if(size != 0){
			qData = malloc(size);
			memcpy(qData, data, size);
		}
		queue->post(facility, qData);
	}
}


EventQueue::EventQueue(size_t count){
	queue = xQueueCreate(count, sizeof(Event));
}

EventQueue::~EventQueue(){
	vQueueDelete(queue);
}

bool EventQueue::get(Event& event, TickType_t timeout){
	return xQueueReceive(queue, &event, timeout) == pdTRUE;
}

bool EventQueue::post(Facility facility, void* data){
	Event event = {
			.facility = facility,
			.data = data
	};

	return xQueueSend(queue, &event, 0) == pdTRUE;
}

void EventQueue::reset(){
	xQueueReset(queue);
}
