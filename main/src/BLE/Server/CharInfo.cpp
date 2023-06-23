#include "../Server.h"
#include <esp_log.h>

static const char* TAG = "BLE::Server::CharInfo";

BLE::Server::CharInfo::CharInfo(Server* server, const Service* service, uint16_t hndl) : server(server), service(service), hndl(hndl){

}

void BLE::Server::CharInfo::addDescr(esp_bt_uuid_t uuid, esp_gatt_perm_t perm){
	if(uuid.len == ESP_UUID_LEN_16){
		uint16_t uid = uuid.uuid.uuid16;
		uint16_t hndl = this->hndl;
		server->descRequests.insert(std::make_pair(uid, hndl));
	}

	esp_ble_gatts_add_char_descr(service->hndl, &uuid, perm, nullptr, nullptr);
}

esp_err_t BLE::Server::CharInfo::sendResp(uint32_t trans, esp_gatt_status_t status, esp_gatt_rsp_t* resp){
	return esp_ble_gatts_send_response(server->iface.hndl, server->con.hndl, trans, status, resp);
}

void BLE::Server::CharInfo::sendNotif(std::vector<uint8_t> data){
	while(data.size()){
		size_t len = std::min(data.size(), (size_t) server->con.MTU_size - 4);
		len = std::max(len, 1U);
		esp_ble_gatts_send_indicate(server->iface.hndl, server->con.hndl, hndl, len, data.data(), false);
		data.erase(data.begin(), data.begin() + len);
	}
}
