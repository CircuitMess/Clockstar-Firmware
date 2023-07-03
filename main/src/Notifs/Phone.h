#ifndef CLOCKSTAR_FIRMWARE_PHONE_H
#define CLOCKSTAR_FIRMWARE_PHONE_H


#include <cstdint>
#include "Bangle.h"
#include "ANCS/Client.h"
#include "NotifSource.h"

class Phone {
public:

	enum class PhoneType {
		None, Android, IPhone
	};

	struct Event {
		enum { Connected, Disconnected, Added, Changed, Removed, Cleared } action;
		PhoneType phoneType;
		union {
			struct { uint32_t id; } addChgRem;
		} data;
	};

	Phone(BLE::Server* server, BLE::Client* client);

	bool isConnected();
	PhoneType getPhoneType();

	Notif getNotif(uint32_t uid);
	std::vector<Notif> getNotifs();

	void doPos(uint32_t id);
	void doNeg(uint32_t id);

private:
	ANCS::Client ancs;
	Bangle bangle;

	NotifSource* current = nullptr;

	void onConnect(NotifSource* src);
	void onDisconnect(NotifSource* src);

	void onAdd(Notif notif);
	void onModify(Notif notif);
	void onRemove(uint32_t id);

	std::vector<Notif> notifs; // TODO: mutex

	auto findNotif(uint32_t id);

};


#endif //CLOCKSTAR_FIRMWARE_PHONE_H
