#ifndef CLOCKSTAR_FIRMWARE_SERVICEINFO_H
#define CLOCKSTAR_FIRMWARE_SERVICEINFO_H

#include "Char.h"
#include <cstdint>
#include <esp_gatt_defs.h>
#include <vector>
#include <memory>

namespace BLE {

class Client;
class CharInfo;

class ServiceInfo {
public:
	ServiceInfo(Client* client,  uint16_t startHndl,  uint16_t endHndl);

	std::vector<esp_gattc_char_elem_t> getChars() const;
	esp_gattc_char_elem_t getCharByUUID(esp_bt_uuid_t uuid) const;

	std::unique_ptr<CharInfo> makeCharInfo(uint16_t hndl);
	void regChar(Char* chr, uint16_t hndl);

private:
	Client* client;

	const uint16_t startHndl;
	const uint16_t endHndl;

};

}


#endif //CLOCKSTAR_FIRMWARE_SERVICEINFO_H
