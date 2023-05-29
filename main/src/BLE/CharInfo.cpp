#include <cstdint>
#include <esp_log.h>
#include "CharInfo.h"
#include "Client.h"

static const char* TAG = "BLE::CharInfo";

CharInfo::CharInfo(const Client* client, uint16_t hndl) : client(client), hndl(hndl){

}

void CharInfo::regForNotify(){
	ESP_LOGV(TAG, "Registering for notify");
	esp_ble_gattc_register_for_notify(client->iface.hndl, (uint8_t*) client->con.addr, hndl);
}

void CharInfo::writeDescr(esp_bt_uuid_t uuid, uint8_t* data, size_t len){
	ESP_LOGV(TAG, "Write to descriptors");

	esp_gattc_descr_elem_t descr;
	uint16_t count = 1;
	auto ret = esp_ble_gattc_get_descr_by_char_handle(client->iface.hndl, client->con.hndl, hndl, uuid, &descr, &count);

	if(ret != ESP_GATT_OK){
		ESP_LOGE(TAG, "Descriptor retrieve error %d\n", ret);
		return;
	}

	if(count == 0){
		ESP_LOGE(TAG, "Retrieved 0 descriptors");
		return;
	}

	// TODO: this function passes the data ptr to the BT thread
	esp_ble_gattc_write_char_descr(client->iface.hndl, client->con.hndl, descr.handle, len, data, ESP_GATT_WRITE_TYPE_RSP, ESP_GATT_AUTH_REQ_NONE);
}

void CharInfo::write(uint8_t* data, size_t len, bool needResponse){
	esp_ble_gattc_write_char(client->iface.hndl, client->con.hndl, hndl, len, data, needResponse ? ESP_GATT_WRITE_TYPE_RSP : ESP_GATT_WRITE_TYPE_NO_RSP, ESP_GATT_AUTH_REQ_NONE);
}
