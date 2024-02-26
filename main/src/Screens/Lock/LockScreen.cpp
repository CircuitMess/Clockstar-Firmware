#include "LockScreen.h"
#include "Util/Services.h"
#include "Theme/theme.h"
#include "Services/Time.h"
#include "Util/stdafx.h"
#include "Screens/MainMenu/MainMenu.h"
#include "Services/SleepMan.h"
#include "LV_Interface/FSLVGL.h"
#include "LV_Interface/InputLVGL.h"

LockScreen::LockScreen() : ts(*((Time*) Services.get(Service::Time))), phone(*((Phone*) Services.get(Service::Phone))), queue(24){
	notifs.reserve(MaxNotifs);
	notifIcons.reserve(MaxIconsCount);

	buildUI();

	if(skin != nullptr && skin->getMain() != nullptr){
		lv_obj_add_event_cb(skin->getMain(), [](lv_event_t* evt){
			auto scr = static_cast<LockScreen*>(evt->user_data);
			scr->setSleep(true);
		}, LV_EVENT_FOCUSED, this);

		lv_obj_add_event_cb(skin->getMain(), [](lv_event_t* evt){
			auto scr = static_cast<LockScreen*>(evt->user_data);
			scr->setSleep(false);

			if(scr->skin != nullptr && scr->skin->getLocker() != nullptr){
				scr->skin->getLocker()->stop();
			}
		}, LV_EVENT_DEFOCUSED, this);
	}
}

void LockScreen::onStarting(){
	prepare();
}

void LockScreen::onStart(){
	queue.reset();
	Events::listen(Facility::Phone, &queue);
	Events::listen(Facility::Time, &queue);
	Events::listen(Facility::Input, &queue);
	setSleep(true);
}

void LockScreen::onStop(){
	Events::unlisten(&queue);
	setSleep(false);
	delete skin;
	skin = nullptr;
}

void LockScreen::setSleep(bool en){
	auto sleep = (SleepMan*) Services.get(Service::Sleep);
	if(!sleep) return;
	sleep->enAltLock(en);
}

void LockScreen::prepare(){
	if(skin != nullptr){
		skin->prepare();
	}

	updateTime(ts.getTime());
	queue.reset();
	updateNotifs();
}

void LockScreen::loop(){
	if(skin != nullptr){
		skin->loop();

		if(skin->getLocker() != nullptr && skin->getLocker()->t() >= 1){
			transition([](){ return std::make_unique<MainMenu>(); });
			return;
		}
	}

	if(millis() - lastTimeUpdate > TimeUpdateInterval){
		updateTime(ts.getTime());
	}

	Event evt;
	while(queue.get(evt, 0)){
		if(evt.facility == Facility::Phone){
			auto data = (Phone::Event*) evt.data;
			processEvt(*data);
		}else if(evt.facility == Facility::Time){
			auto data = (Time::Event*) evt.data;
			if(data->action == Time::Event::Updated){
				updateTime(data->updated.time);
			}
		}else if(evt.facility == Facility::Input){
			auto data = (Input::Data*) evt.data;
			processInput(*data);
		}
		free(evt.data);
	}
}

void LockScreen::processInput(const Input::Data& evt){
	if(skin == nullptr){
		return;
	}

	if(evt.btn == Input::Alt && evt.action == Input::Data::Press && lv_group_get_focused(inputGroup) != skin->getMain()){
		lv_group_focus_obj(skin->getMain());
		return;
	}

	if(lv_group_get_focused(inputGroup) != skin->getMain()) return;

	if(evt.btn == Input::Select){
		if(evt.action == Input::Data::Press){
			skin->getLocker()->start();
		}else if(evt.action == Input::Data::Release){
			bool hide = skin->getLocker()->t() < 0.05;
			skin->getLocker()->stop();
			if(hide){
				skin->getLocker()->hide();
			}
		}
	}
}

void LockScreen::processEvt(const Phone::Event& evt){
	if(evt.action == Phone::Event::Added || evt.action == Phone::Event::Changed){
		auto notif = phone.getNotif(evt.data.addChgRem.id);
		notifAdd(notif);
	}else if(evt.action == Phone::Event::Removed){
		notifRem(evt.data.addChgRem.id);
	}else if(evt.action == Phone::Event::Cleared){
		notifsClear();
	}
}

void LockScreen::updateNotifs(){
	/*const auto set = phone.getNotifs();
	auto find = [&set](uint32_t uid) -> const Notif*{
		for(auto& notif : set){
			if(notif.uid == uid) return &notif;
		}
		return nullptr;
	};

	std::unordered_set<uint32_t> forRem;
	for(const auto& pair : notifs){
		auto exists = find(pair.first);
		if(!exists){
			forRem.insert(pair.first);
		}
	}
	for(uint32_t uid : forRem){
		notifRem(uid);
	}

	for(const auto& notif : set){
		if(notifs.count(notif.uid) == 0){
			notifAdd(notif);
		}
	}*/
}

void LockScreen::notifAdd(const Notif& notif){
	/*bool isModify = true;

	if(skin == nullptr){
		return;
	}

	if(notifs.count(notif.uid) == 0){
		if(notifs.size() >= MaxNotifs) return;

		isModify = false;

		auto uid = notif.uid;
		auto item = new Item(rest, [this, uid](){
			notifRem(uid);
			phone.doNeg(uid);
		});

		bool itemActive = false;
		if(InputLVGL::getInstance()->getIndev()->group != inputGroup){
			itemActive = true;
		}

		auto focused = lv_group_get_focused(inputGroup);
		lv_obj_move_to_index(*item, 0);
		lv_group_remove_all_objs(inputGroup);
		lv_group_add_obj(inputGroup, skin->getMain());
		for(int j = 0; j < lv_obj_get_child_cnt(rest); ++j){
			lv_group_add_obj(inputGroup, lv_obj_get_child(rest, j));
		}

		lv_group_focus_obj(focused);
		if(itemActive){
			lv_event_send(focused, LV_EVENT_CLICKED, nullptr);
		}

		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_CHAIN_VER);

		notifs.insert(std::make_pair(notif.uid, item));

		addNotifIcon(iconPath(notif));
	}

	auto el = notifs[notif.uid];

	if(isModify){
		removeNotifIcon(el->iconPath());
		addNotifIcon(iconPath(notif));
	}
	el->update(notif);*/
}

void LockScreen::notifRem(uint32_t id){
	/*auto it = notifs.find(id);
	if(it == notifs.end()) return;
	auto& el = it->second;

	removeNotifIcon(el->iconPath());
	lv_group_focus_next(inputGroup);

	lv_obj_del(*el);
	notifs.erase(it);*/
}

void LockScreen::notifsClear(){
	/*notifs.clear(); // This has to precede rest clearing
	lv_obj_clean(rest);

	notifIcons.clear();
	lv_obj_clean(icons);*/
}


void LockScreen::addNotifIcon(const char* path){
	/*if(path == nullptr) return;

	if(notifIcons.count(path)){
		notifIcons[path].count++;
		return;
	}

	if(notifIcons.size() >= MaxIconsCount) return;


	lv_obj_t* icon = lv_img_create(icons);
	lv_img_set_src(icon, path);

	NotifIcon notifIcon = { 1, icon };
	notifIcons.insert({ path, notifIcon });*/
}

void LockScreen::removeNotifIcon(const char* path){
	/*if(path == nullptr) return;

	auto pair = notifIcons.find(path);
	if(pair == notifIcons.end()) return;

	pair->second.count -= 1;
	if(pair->second.count > 0) return;

	lv_obj_del(pair->second.icon);
	notifIcons.erase(pair);*/
}

void LockScreen::updateTime(const tm& time){
	lastTimeUpdate = millis();

	// Update any date/time in UI here

	/*char dateText[128];

	static const char* Months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	const int dayLd = time.tm_mday - (time.tm_mday / 10) * 10;
	const char* daySuff;
	if(time.tm_mday == 11 || time.tm_mday == 12) daySuff = "th";
	else if(dayLd == 1) daySuff = "st";
	else if(dayLd == 2) daySuff = "nd";
	else if(dayLd == 3) daySuff = "rd";
	else daySuff = "th";

	snprintf(dateText, sizeof(dateText), "%s %d%s, %d", Months[time.tm_mon % 12], time.tm_mday, daySuff, 1900 + time.tm_year);*/
}

void LockScreen::buildUI(){
	skin = new LockSkin(*this, inputGroup);

	// TODO: this may not be needed
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);
}
