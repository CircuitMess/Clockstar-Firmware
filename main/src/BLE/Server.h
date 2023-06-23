#ifndef CLOCKSTAR_FIRMWARE_BLE_SERVER_H
#define CLOCKSTAR_FIRMWARE_BLE_SERVER_H

#include <cstdint>
#include <cstring>
#include <vector>
#include <memory>
#include <functional>
#include <unordered_set>
#include <unordered_map>
#include <Util/Queue.h>
#include <esp_bt_defs.h>
#include <esp_gatt_defs.h>
#include <esp_gatts_api.h>

namespace BLE {

class GAP;

class Server {
public:
	class Service;
	class Char;
	class CharInfo;
#include "Server/Service.h"
#include "Server/Char.h"
#include "Server/CharInfo.h"

	Server(GAP* gap);
	virtual ~Server();

	std::shared_ptr<Service> addService(esp_bt_uuid_t uuid);

	void start();

	using ConnectCB = std::function<void(const esp_bd_addr_t)>;
	using DisconnectCB = std::function<void(const esp_bd_addr_t)>;
	void setOnConnectCb(ConnectCB cb);
	void setOnDisconnectCb(DisconnectCB cb);

private:
	static Server* self;
	friend CharInfo;

	std::unordered_set<std::shared_ptr<Service>> services;
	std::unordered_map<uint16_t, Char*> chars;
	std::unordered_map<uint16_t, uint16_t> descRequests; // descr uuid -> char hndl

	ConnectCB onConnectCB;
	DisconnectCB onDisconnectCB;

	friend GAP;
	GAP* gap;
	void onPairDone();

	static constexpr int AppID = 1;
	struct InterfaceInfo {
		uint8_t appID = 0xff;
		uint8_t hndl = 0xff;

		operator bool(){ return appID != 0xff && hndl != 0; }
	} iface;

	struct ConnectionInfo {
		esp_bd_addr_t addr;
		uint16_t hndl = 0xffff;

		uint16_t MTU_size = 23;

		operator bool(){ return hndl != 0xffff; }
	} con;

	void ble_GATTS_cb(esp_gatts_cb_event_t event, esp_gatt_if_t gattc_if, esp_ble_gatts_cb_param_t *param);

	void registerServices();
	void onServiceCreated(const esp_ble_gatts_cb_param_t::gatts_create_evt_param* param);
	void onCharCreated(const esp_ble_gatts_cb_param_t::gatts_add_char_evt_param* param);
	void onCharDescrCreated(const esp_ble_gatts_cb_param_t::gatts_add_char_descr_evt_param* param);

	void onMtuResp(const esp_ble_gatts_cb_param_t::gatts_mtu_evt_param* param);
	void onConnect(const esp_ble_gatts_cb_param_t::gatts_connect_evt_param* param);
	void onDisconnect(const esp_ble_gatts_cb_param_t::gatts_disconnect_evt_param* param);

	void passToChar(esp_gatts_cb_event_t event, const esp_ble_gatts_cb_param_t* param);

};

}

#endif //CLOCKSTAR_FIRMWARE_BLE_SERVER_H
