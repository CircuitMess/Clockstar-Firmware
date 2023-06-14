#include "NotifSource.h"

void NotifSource::connect(){
	if(onConnect) onConnect();
}

void NotifSource::disconnect(){
	if(onDisconnect) onDisconnect();
}

void NotifSource::notifNew(Notif notif){
	if(onNotifAdd) onNotifAdd(notif);
}

void NotifSource::notifModify(Notif notif){
	if(onNotifModify) onNotifModify(notif);
}

void NotifSource::notifRemove(uint32_t uid){
	if(onNotifRemove) onNotifRemove(uid);
}

void NotifSource::setOnConnect(NotifSource::ConnectCB onConnect){
	NotifSource::onConnect = std::move(onConnect);
}

void NotifSource::setOnDisconnect(NotifSource::ConnectCB onDisconnect){
	NotifSource::onDisconnect = std::move(onDisconnect);
}

void NotifSource::setOnNotifAdd(NotifSource::NotifAddCB onNotifAdd){
	NotifSource::onNotifAdd = std::move(onNotifAdd);
}

void NotifSource::setOnNotifModify(NotifSource::NotifModifyCB onNotifModify){
	NotifSource::onNotifModify = std::move(onNotifModify);
}

void NotifSource::setOnNotifRemove(NotifSource::NotifRemoveCB onNotifRemove){
	NotifSource::onNotifRemove = std::move(onNotifRemove);
}
