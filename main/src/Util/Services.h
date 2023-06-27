#ifndef CLOCKSTAR_FIRMWARE_SERVICES_H
#define CLOCKSTAR_FIRMWARE_SERVICES_H

#include <unordered_map>

enum class Service { IMU };

class ServiceLocator {
public:
	void set(Service service, void* ptr);
	void* get(Service service);

private:
	std::unordered_map<Service, void*> services;


};

extern ServiceLocator Services;

#endif //CLOCKSTAR_FIRMWARE_SERVICES_H