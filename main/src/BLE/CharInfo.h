#ifndef CLOCKSTAR_FIRMWARE_CHARINFO_H
#define CLOCKSTAR_FIRMWARE_CHARINFO_H

#include <cstdint>
#include <stddef.h>
#include <esp_bt_defs.h>

class Client;

class CharInfo {
public:
	CharInfo(const Client* client, uint16_t hndl);

	void regForNotify();

	void writeDescr(esp_bt_uuid_t uuid, uint8_t* data, size_t len);

	void write(uint8_t* data, size_t len, bool needResponse);

private:
	const Client* client;

	const uint16_t hndl;

};


#endif //CLOCKSTAR_FIRMWARE_CHARINFO_H
