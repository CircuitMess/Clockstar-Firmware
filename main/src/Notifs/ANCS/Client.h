#ifndef CLOCKSTAR_FIRMWARE_ANCS_H
#define CLOCKSTAR_FIRMWARE_ANCS_H

#include <BLE/Client.h>
#include "Notifs/NotifSource.h"
#include "Util/Threaded.h"
#include "Model.h"
#include <queue>
#include <deque>
#include <mutex>

namespace ANCS {

class Client : public NotifSource {
public:
	Client(BLE::Client* client);
	virtual ~Client();

	void actionPos(uint32_t uid) override;
	void actionNeg(uint32_t uid) override;

private:
	std::shared_ptr<BLE::Client::Service> service;
	struct {
		std::shared_ptr<BLE::Client::Char> notif;
		std::shared_ptr<BLE::Client::Char> ctrl;
		std::shared_ptr<BLE::Client::Char> data;
	} chr;

	bool connected = false;

	void onConn();
	void onDiscon();

	ThreadedClosure notifThread;
	ThreadedClosure dataThread;

	void loopNotif();
	void loopData();

	struct QueuedNotif {
		uint32_t uid;
		CategoryID category;
		bool modify; // whether it's a new notification or a modification
		std::unordered_map<AttributeID, std::string> attrs;
	};
	std::queue<QueuedNotif> needData;
	std::mutex needDataMut;

	void requestData(uint32_t uid);
	void processData(bool sendIncomplete);
	std::deque<uint8_t> dataQueue;
	bool processingAttrs = false;

	static constexpr esp_bt_uuid_t ServiceUUID =			{ .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xD0, 0x00, 0x2D, 0x12, 0x1E, 0x4B, 0x0F, 0xA4, 0x99, 0x4E, 0xCE, 0xB5, 0x31, 0xF4, 0x05, 0x79 }}};
	static constexpr esp_bt_uuid_t Char_NotifSource_UUID =	{ .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xbd, 0x1d, 0xa2, 0x99, 0xe6, 0x25, 0x58, 0x8c, 0xd9, 0x42, 0x01, 0x63, 0x0d, 0x12, 0xbf, 0x9f }}};
	static constexpr esp_bt_uuid_t Char_ControlPoint_UUID =	{ .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xd9, 0xd9, 0xaa, 0xfd, 0xbd, 0x9b, 0x21, 0x98, 0xa8, 0x49, 0xe1, 0x45, 0xf3, 0xd8, 0xd1, 0x69 }}};
	static constexpr esp_bt_uuid_t Char_DataSource_UUID =	{ .len = ESP_UUID_LEN_128, .uuid = { .uuid128 = { 0xfb, 0x7b, 0x7c, 0xce, 0x6a, 0xb3, 0x44, 0xbe, 0xb5, 0x4b, 0xd6, 0x24, 0xe9, 0xc6, 0xea, 0x22 }}};

};

}


#endif //CLOCKSTAR_FIRMWARE_CLIENT_H
