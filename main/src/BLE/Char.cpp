#include <esp_log.h>
#include "Char.h"

static const char* TAG = "BLE::Char";

Char::Char(esp_bt_uuid_t uuid, esp_gatt_char_prop_t props) : uuid(uuid), props(props){

}

void Char::setOnConnectedCb(ConnectedCB cb){
	onConnectedCB = cb;
}

void Char::setOnNotifyCb(NotifyCB cb){
	if(!(props & ESP_GATT_CHAR_PROP_BIT_NOTIFY)){
		ESP_LOGW(TAG, "Notify CB set, but NOTIFY property bit isn't");
	}

	onNotifyCB = std::move(cb);
}

bool Char::established(){
	return chr != nullptr;
}

bool Char::connected(){
	return configsDone.size() == (int) Config::COUNT;
}

void Char::establish(std::unique_ptr<CharInfo> info, esp_gatt_char_prop_t rProps){
	ESP_LOGI(TAG, "Established");
	chr = std::move(info);

	remoteProps = rProps;

	if(props & ESP_GATT_CHAR_PROP_BIT_NOTIFY){
		if(remoteProps & ESP_GATT_CHAR_PROP_BIT_NOTIFY){
			chr->regForNotify();
		}else{
			ESP_LOGW(TAG, "Have NOTIFY bit set, but remote characteristic doesn't");
		}
	}else{
		configDone(Config::Notify);
	}
}

void Char::close(){
	if(!chr) return;
	ESP_LOGI(TAG, "Closed");

	chr.reset();
	remoteProps = 0;
	configsDone.clear();
}

void Char::configDone(Char::Config config){
	configsDone.insert(config);
	if(configsDone.size() == (int) Config::COUNT){
		if(onConnectedCB){
			onConnectedCB();
		}
	}
}

void Char::onRegNotify(const esp_ble_gattc_cb_param_t::gattc_reg_for_notify_evt_param* param){
	if(param->status != ESP_GATT_OK){
		ESP_LOGE(TAG, "reg for notify failed, error status = 0x%x", param->status);
		return;
	}

	ESP_LOGI(TAG, "Registered for notify");
	configDone(Config::Notify);
}

void Char::onNotify(const esp_ble_gattc_cb_param_t::gattc_notify_evt_param* param){
	if(onNotifyCB){
		onNotifyCB(std::vector(param->value, param->value + param->value_len), !param->is_notify);
	}
}

void Char::writeDescr(uint16_t uuid, const std::vector<uint8_t>& data){
	if(!connected()) return;

	esp_bt_uuid_t id = { .len = 2 };
	id.uuid.uuid16 = uuid;
	chr->writeDescr(id, (uint8_t*) data.data(), data.size());
}
