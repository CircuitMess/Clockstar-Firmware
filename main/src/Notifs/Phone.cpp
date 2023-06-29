#include "Phone.h"
#include "Util/Events.h"

Phone::Phone(BLE::Server* server, BLE::Client* client) : ancs(client), bangle(server){
	notifs.reserve(32);

	auto reg = [this](NotifSource* src){
		src->setOnConnect([this, src](){ onConnect(src); });
		src->setOnDisconnect([this, src](){ onDisconnect(src); });
		src->setOnNotifAdd([this](Notif notif){ onAdd(std::move(notif)); });
		src->setOnNotifModify([this](Notif notif){ onModify(std::move(notif)); });
		src->setOnNotifRemove([this](uint32_t id){ onRemove(id); });
	};

	reg(&ancs);
	reg(&bangle);
}

bool Phone::isConnected(){
	return current != nullptr;
}

auto Phone::findNotif(uint32_t id){
	return std::find_if(notifs.begin(), notifs.end(), [id](const auto& notif){ return notif.uid == id; });
}

Notif Phone::getNotif(uint32_t uid){
	auto notif = findNotif(uid);
	if(notif == notifs.end()) return {};
	return *notif;
}

std::vector<Notif> Phone::getNotifs(){
	return notifs;
}

void Phone::doPos(uint32_t id){
	if(current == nullptr || findNotif(id) == notifs.end()) return;
	current->actionPos(id);
}

void Phone::doNeg(uint32_t id){
	if(current == nullptr || findNotif(id) == notifs.end()) return;
	current->actionNeg(id);
}

void Phone::onConnect(NotifSource* src){
	current = src;
	Events::post(Facility::Phone, Event { .action = Event::Connected });

	if(!notifs.empty()){
		notifs.clear();
		Events::post(Facility::Phone, Event { .action = Event::Cleared });
	}
}

void Phone::onDisconnect(NotifSource* src){
	if(current != src) return;
	current = nullptr;
	Events::post(Facility::Phone, Event { .action = Event::Disconnected });

	if(!notifs.empty()){
		notifs.clear();
		Events::post(Facility::Phone, Event { .action = Event::Cleared });
	}
}

void Phone::onAdd(Notif notif){
	if(findNotif(notif.uid) != notifs.end()) return;
	if(notifs.size() + 1 == notifs.capacity()){
		notifs.reserve(notifs.capacity() * 2);
	}

	notifs.push_back(notif); // TODO: send whole notification, otherwise (by using a mutex) all newly unlocked tasks will rush after getNotif, and promptly get locked again by the mutex
	Events::post(Facility::Phone, Event { .action = Event::Added, .data = { .addChgRem = { .id = notif.uid } } });
}

void Phone::onModify(Notif notif){
	auto saved = findNotif(notif.uid);
	if(saved == notifs.end()){
		onAdd(std::move(notif));
		return;
	}

	*saved = notif;
	Events::post(Facility::Phone, Event { .action = Event::Changed, .data = { .addChgRem = { .id = notif.uid } } });
}

void Phone::onRemove(uint32_t id){
	auto notif = findNotif(id);
	if(notif == notifs.end()) return;

	notifs.erase(notif);
	Events::post(Facility::Phone, Event { .action = Event::Removed, .data = { .addChgRem = { .id = id } } });
}
