#ifndef CLOCKSTAR_FIRMWARE_CONCONF_H
#define CLOCKSTAR_FIRMWARE_CONCONF_H

#include <esp_gap_ble_api.h>
#include <freertos/semphr.h>
#include <unordered_set>
#include <mutex>

class ConConf {
public:

	void conf(const esp_ble_conn_update_params_t& params);
	void waitDone(TickType_t wait);
	void confDone(bool success);
	void reset();

private:
	esp_ble_conn_update_params_t current = {};
	esp_ble_conn_update_params_t pending = {};
	std::mutex confMut;

	bool hasCurrent() const;
	bool hasPending() const;

	void send(esp_ble_conn_update_params_t params);

	std::unordered_set<SemaphoreHandle_t> waitSems;
	std::mutex waitMut;

};


#endif //CLOCKSTAR_FIRMWARE_CONCONF_H
