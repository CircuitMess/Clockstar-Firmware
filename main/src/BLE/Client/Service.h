#ifdef CLOCKSTAR_FIRMWARE_BLE_CLIENT_H

class Service {
public:
	std::shared_ptr<BLE::Client::Char> addChar(esp_bt_uuid_t uuid, esp_gatt_char_prop_t props = 0);

	bool established();
	bool populated();

	using ConnectCB = std::function<void()>;
	using DisconnectCB = std::function<void()>;
	void setOnConnectCb(ConnectCB onConnectCb);
	void setOnDisconnectCb(DisconnectCB onConnectCb);

private:
	friend BLE::Client;
	Service(esp_bt_uuid_t uuid);

	esp_bt_uuid_t uuid;
	std::unordered_set<std::shared_ptr<BLE::Client::Char>> chars;

	std::unique_ptr<BLE::Client::ServiceInfo> svc;

	void establish(std::unique_ptr<BLE::Client::ServiceInfo> info);
	void pull();
	void close();

	ConnectCB onConnectCB;
	DisconnectCB onDisconnectCB;

};

#endif //CLOCKSTAR_FIRMWARE_BLE_CLIENT_H
