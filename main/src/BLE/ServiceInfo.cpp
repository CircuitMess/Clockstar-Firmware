#include "ServiceInfo.h"
#include "Client.h"
#include "Char.h"
#include <esp_log.h>

static const char* TAG = "BLE::ServiceInfo";

ServiceInfo::ServiceInfo(Client* client, uint16_t startHndl, uint16_t endHndl) : client(client), startHndl(startHndl), endHndl(endHndl){

}

std::vector<esp_gattc_char_elem_t> ServiceInfo::getChars() const{
	uint16_t count;
	auto ret = esp_ble_gattc_get_attr_count(client->iface.hndl, client->con.hndl, ESP_GATT_DB_CHARACTERISTIC, startHndl, endHndl, 0, &count);
	if(ret != ESP_GATT_OK){
		ESP_LOGE(TAG, "get_attr_count error 0x%x", ret);
		return {};
	}

	std::vector<esp_gattc_char_elem_t> chars(count);

	ret = esp_ble_gattc_get_all_char(client->iface.hndl, client->con.hndl, startHndl, endHndl, chars.data(), &count, 0);
	if(ret != ESP_GATT_OK){
		ESP_LOGE(TAG, "get_all_char error 0x%x", ret);
		return {};
	}

	return chars;
}

esp_gattc_char_elem_t ServiceInfo::getCharByUUID(esp_bt_uuid_t uuid) const{
	esp_gattc_char_elem_t chr;
	uint16_t count = 1;

	auto ret = esp_ble_gattc_get_char_by_uuid(client->iface.hndl, client->con.hndl, startHndl, endHndl, uuid, &chr, &count);
	if(ret != ESP_GATT_OK){
		ESP_LOGE(TAG, "get_char_by_uuid error 0x%x for uuid ", ret);
		esp_log_buffer_hex(TAG, uuid.uuid.uuid128, 16);
		return {};
	}

	if(count == 0) return {};

	return chr;
}

std::unique_ptr<CharInfo> ServiceInfo::makeCharInfo(uint16_t hndl){
	return std::make_unique<CharInfo>(client, hndl);
}

void ServiceInfo::regChar(Char* chr, uint16_t hndl){
	client->chars.insert(std::make_pair(hndl, chr));
}