#ifndef CLOCKSTAR_FIRMWARE_SERVICE_H
#define CLOCKSTAR_FIRMWARE_SERVICE_H


#include "Char.h"
#include "ServiceInfo.h"
#include <esp_bt_defs.h>
#include <unordered_set>
#include <memory>

namespace BLE {

class Client;

class Service {
public:
	std::shared_ptr<Char> addChar(esp_bt_uuid_t uuid, esp_gatt_char_prop_t props = 0);

	bool established();
	bool populated();

	using ConnectCB = std::function<void()>;
	using DisconnectCB = std::function<void()>;
	void setOnConnectCb(ConnectCB onConnectCb);
	void setOnDisconnectCb(DisconnectCB onConnectCb);

private:
	friend Client;
	Service(esp_bt_uuid_t uuid);

	esp_bt_uuid_t uuid;
	std::unordered_set<std::shared_ptr<Char>> chars;

	std::unique_ptr<ServiceInfo> svc;

	void establish(std::unique_ptr<ServiceInfo> info);
	void pull();
	void close();

	ConnectCB onConnectCB;
	DisconnectCB onDisconnectCB;

};

}


#endif //CLOCKSTAR_FIRMWARE_SERVICE_H
