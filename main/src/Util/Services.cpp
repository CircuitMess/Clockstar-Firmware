#include "Services.h"

ServiceLocator Services;

void ServiceLocator::set(Service service, void* ptr){
	services[service] = ptr;
}

void* ServiceLocator::get(Service service){
	if(!services.count(service)) return nullptr;
	return services[service];
}
