#ifdef CLOCKSTAR_FIRMWARE_BLE_SERVER_H


class Char {
public:

	struct WriteMsg {
		std::vector<uint8_t> data;
		WriteMsg(std::vector<uint8_t> data) : data(std::move(data)){}
	};

	std::unique_ptr<WriteMsg> getNextWrite(TickType_t wait = portMAX_DELAY);

	void sendNotif(const std::vector<uint8_t>& data);

	using WriteCB = std::function<void(const std::vector<uint8_t>& data)>;
	void setOnWriteCb(WriteCB cb);

private:
	friend BLE::Server;
	friend BLE::Server::Service;
	Char(esp_bt_uuid_t uuid, esp_gatt_char_prop_t props);

	esp_bt_uuid_t uuid;
	esp_gatt_char_prop_t props;
	esp_gatt_perm_t perm = 0;

	WriteCB onWriteCB;
	PtrQueue<WriteMsg> writeQueue;

	std::unique_ptr<BLE::Server::CharInfo> chr;
	void establish(std::unique_ptr<BLE::Server::CharInfo> info);

	void onRead(const esp_ble_gatts_cb_param_t::gatts_read_evt_param* param);
	void onWrite(const esp_ble_gatts_cb_param_t::gatts_write_evt_param* param);
	void onExecWrite(const esp_ble_gatts_cb_param_t::gatts_exec_write_evt_param* param);

	// TODO: reset on disconnect
	bool notifyEn = false;
	bool indicateEn = false;

	uint16_t ctrlDescrHndl = 0xffff;

	std::vector<uint8_t> writeData; // TODO: clear on disconnect

};


#endif //CLOCKSTAR_FIRMWARE_BLE_SERVER_H
