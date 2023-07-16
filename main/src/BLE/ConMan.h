#ifndef CLOCKSTAR_FIRMWARE_CONMAN_H
#define CLOCKSTAR_FIRMWARE_CONMAN_H

#include "GAP.h"
#include "ConConf.h"
#include <esp_gap_ble_api.h>

class ConManager {
public:

	void connect(const esp_bd_addr_t addr);
	void disconnect();

	void goLowPow();
	void goHiPow();

private:
	friend BLE::GAP;
	void confDone(bool success);
	ConConf conConf;

	bool connected = false;
	esp_bd_addr_t current;

	bool lowPow = false;

	void setAdv();
	void setCon();

	static constexpr esp_ble_adv_params_t AdvLowPow = {
			.adv_int_min        = 2056, // 1285ms = 2056 * 0.625ms
			.adv_int_max        = 2056, // Apple: Interval should be 20ms. After 30 seconds of no connection, feel free to switch to 1285ms
			.adv_type           = ADV_TYPE_IND,
			.own_addr_type      = BLE_ADDR_TYPE_RPA_PUBLIC,
			.channel_map        = ADV_CHNL_ALL,
			.adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
	};

	static constexpr esp_ble_adv_params_t AdvHiPow = {
			.adv_int_min        = 32, // 20ms = 32 * 0.625ms
			.adv_int_max        = 32,
			.adv_type           = ADV_TYPE_IND,
			.own_addr_type      = BLE_ADDR_TYPE_RPA_PUBLIC,
			.channel_map        = ADV_CHNL_ALL,
			.adv_filter_policy  = ADV_FILTER_ALLOW_SCAN_ANY_CON_ANY,
	};

	static constexpr esp_ble_conn_update_params_t ConLowPow = {
			.min_int = 960, // min_int = 480*1.25ms = 600ms
			.max_int = 1200, // max_int = 600*1.25ms = 750ms
			.latency = 0,
			.timeout = 600 // timeout = 500*10ms = 5000ms
	};

	static constexpr esp_ble_conn_update_params_t ConHiPow = {
			.min_int = 24, // min_int = 24*1.25ms = 30ms
			.max_int = 40, // max_int = 40*1.25ms = 50ms
			.latency = 0,
			.timeout = 400 // timeout = 500*10ms = 5000ms
	};

};

extern ConManager ConMan;

#endif //CLOCKSTAR_FIRMWARE_CONMAN_H
