#ifdef CLOCKSTAR_FIRMWARE_BLE_SERVER_H

class CharInfo {
public:
	CharInfo(BLE::Server* server, const BLE::Server::Service* service, uint16_t hndl);

	/*void regForNotify();

	void writeDescr(esp_bt_uuid_t uuid, uint8_t* data, size_t len);

	void write(uint8_t* data, size_t len, bool needResponse);*/

	void addDescr(esp_bt_uuid_t uuid, esp_gatt_perm_t perm);

	esp_err_t sendResp(uint32_t trans, esp_gatt_status_t status, esp_gatt_rsp_t* resp = nullptr);

	void sendNotif(std::vector<uint8_t> data);

private:
	BLE::Server* server;
	const BLE::Server::Service* service;

	const uint16_t hndl;

};

#endif //CLOCKSTAR_FIRMWARE_BLE_CLIENT_H
