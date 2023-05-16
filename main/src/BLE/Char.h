#ifndef CLOCKSTAR_FIRMWARE_CHAR_H
#define CLOCKSTAR_FIRMWARE_CHAR_H


#include "CharInfo.h"
#include <esp_bt_defs.h>
#include <memory>
#include <esp_gatt_defs.h>
#include <functional>
#include <vector>
#include <esp_gattc_api.h>
#include <unordered_set>

class Service;

class Char {
public:

	bool established();
	bool connected();

	using NotifyCB = std::function<void(const std::vector<uint8_t>& data, bool isIndicate)>;
	using ConnectedCB = std::function<void()>;

	void setOnNotifyCb(NotifyCB cb);
	void setOnConnectedCb(ConnectedCB cb);

	void writeDescr(uint16_t uuid, const std::vector<uint8_t>& data);

private:
	friend Client;
	friend Service;
	Char(esp_bt_uuid_t uuid, esp_gatt_char_prop_t props);

	esp_bt_uuid_t uuid;
	esp_gatt_char_prop_t props;
	esp_gatt_char_prop_t remoteProps;

	std::unique_ptr<CharInfo> chr;

	void establish(std::unique_ptr<CharInfo> info, esp_gatt_char_prop_t rProps);
	void close();

	enum class Config {
		Notify,
		COUNT
	};
	std::unordered_set<Config> configsDone;
	void configDone(Config config);

	ConnectedCB onConnectedCB;
	NotifyCB onNotifyCB;

	void onNotify(const esp_ble_gattc_cb_param_t::gattc_notify_evt_param* param);
	void onRegNotify(const esp_ble_gattc_cb_param_t::gattc_reg_for_notify_evt_param* param);

};


#endif //CLOCKSTAR_FIRMWARE_CHAR_H