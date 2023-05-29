#ifndef CLOCKSTAR_FIRMWARE_NOTIFSOURCE_H
#define CLOCKSTAR_FIRMWARE_NOTIFSOURCE_H

#include "Notif.h"
#include <functional>

class NotifSource {
public:

	using ConnectCB = std::function<void()>;
	using DisconnectCB = std::function<void()>;

	using NotifAddCB = std::function<void(Notif notif)>;
	using NotifModifyCB = std::function<void(Notif notif)>;
	using NotifRemoveCB = std::function<void(uint32_t uid)>;

	void setOnConnect(ConnectCB onConnect);
	void setOnDisconnect(ConnectCB onDisconnect);

	void setOnNotifAdd(NotifAddCB onNotifAdd);
	void setOnNotifModify(NotifModifyCB onNotifModify);
	void setOnNotifRemove(NotifRemoveCB onNotifRemove);

	virtual void actionPos(uint32_t uid) = 0;
	virtual void actionNeg(uint32_t uid) = 0;

protected:

	void connect();
	void disconnect();

	void notifNew(Notif notif);
	void notifModify(Notif notif);
	void notifRemove(uint32_t uid);

private:

	ConnectCB onConnect;
	ConnectCB onDisconnect;

	NotifAddCB onNotifAdd;
	NotifModifyCB onNotifModify;
	NotifRemoveCB onNotifRemove;

};

#endif //CLOCKSTAR_FIRMWARE_NOTIFSOURCE_H
