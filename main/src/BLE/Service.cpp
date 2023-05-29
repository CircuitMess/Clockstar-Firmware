#include <cstring>
#include <esp_log.h>
#include "Service.h"

static const char* TAG = "BLE::Service";

BLE::Service::Service(esp_bt_uuid_t uuid) : uuid(uuid){

}

std::shared_ptr<BLE::Char> BLE::Service::addChar(esp_bt_uuid_t uuid, esp_gatt_char_prop_t props){
	std::shared_ptr<Char> chr(new Char(uuid, props));
	chars.insert(chr);
	return chr;
}

void BLE::Service::setOnConnectCb(Service::ConnectCB onConnectedCb){
	onConnectCB = std::move(onConnectedCb);
}

void BLE::Service::setOnDisconnectCb(Service::DisconnectCB onDisconnectCb){
	onDisconnectCB = std::move(onDisconnectCb);
}

bool BLE::Service::established(){
	return svc != nullptr;
}

bool BLE::Service::populated(){
	for(const auto& chr : chars){
		if(chr->established()) return true;
	}

	return false;
}

void BLE::Service::establish(std::unique_ptr<ServiceInfo> info){
	ESP_LOGI(TAG, "Established");
	svc = std::move(info);
}

void BLE::Service::pull(){
	if(!svc) return;

	for(const auto& chr : chars){
		auto remote = svc->getCharByUUID(chr->uuid);
		if(remote.uuid.len == 0){
			ESP_LOGW(TAG, "Registered characteristic not found in remote service. Char UUID: ");
			esp_log_buffer_hex(TAG, chr->uuid.uuid.uuid128, 16);
			continue;
		}

		// TODO: refactor this or something
		svc->regChar(chr.get(), remote.char_handle);
		chr->establish(svc->makeCharInfo(remote.char_handle), remote.properties);
	}

	if(onConnectCB){
		onConnectCB();
	}
}

void BLE::Service::close(){
	if(!svc) return;
	ESP_LOGI(TAG, "Closing");

	for(const auto& chr : chars){
		chr->close();
	}

	svc.reset();

	if(onDisconnectCB){
		onDisconnectCB();
	}
}
