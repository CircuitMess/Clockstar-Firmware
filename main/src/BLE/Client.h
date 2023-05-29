#ifndef CLOCKSTAR_FIRMWARE_CLIENT_H
#define CLOCKSTAR_FIRMWARE_CLIENT_H

#include "Service.h"
#include <memory>
#include <esp_gattc_api.h>

namespace BLE {

class ServiceInfo;
class GAP;

class Client {
public:
	Client(GAP* gap);
	~Client();

	std::shared_ptr<Service> addService(esp_bt_uuid_t uuid);

private:
	static Client* self;
	friend ServiceInfo;
	friend CharInfo;
	friend GAP;

	std::unordered_set<std::shared_ptr<Service>> services;
	std::unordered_map<uint16_t, Char*> chars;

	static constexpr int AppID = 0;
	struct InterfaceInfo {
		uint8_t appID = 0xff;
		uint8_t hndl = 0xff;

		operator bool(){ return appID != 0xff && hndl != 0; }
	} iface;

	struct ConnectionInfo {
		esp_bd_addr_t addr;
		uint16_t hndl = 0xffff;

		uint16_t MTU_size = 500;

		operator bool(){ return hndl != 0xffff; }
	} con;

	void ble_GATTC_cb(esp_gattc_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gattc_cb_param_t *param);

	GAP* gap;
	void onPairDone();

	void onConnect(const esp_ble_gattc_cb_param_t::gattc_connect_evt_param* param);
	void onOpen(const esp_ble_gattc_cb_param_t::gattc_open_evt_param* param);
	void onMtuResp(const esp_ble_gattc_cb_param_t::gattc_cfg_mtu_evt_param* param);

	void searchServices();
	void onSearchResult(const esp_ble_gattc_cb_param_t::gattc_search_res_evt_param* param);
	void onSearchComplete(const esp_ble_gattc_cb_param_t::gattc_search_cmpl_evt_param* param);

	void onClose(const esp_ble_gattc_cb_param_t::gattc_close_evt_param* param);
	void onDisconnect(const esp_ble_gattc_cb_param_t::gattc_disconnect_evt_param* param);

	void passToChar(esp_gattc_cb_event_t event, esp_ble_gattc_cb_param_t *param);
	void close();

};

}


#endif //CLOCKSTAR_FIRMWARE_CLIENT_H
