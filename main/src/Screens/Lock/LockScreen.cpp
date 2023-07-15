#include "LockScreen.h"
#include "Util/Services.h"
#include "Theme/theme.h"
#include "Services/Time.h"
#include "Util/stdafx.h"
#include "Screens/MainMenu/MainMenu.h"
#include "Services/Sleep.h"

LockScreen::LockScreen() : ts(*((Time*) Services.get(Service::Time))), phone(*((Phone*) Services.get(Service::Phone))), queue(12){
	buildUI();
	Events::listen(Facility::Phone, &queue);
	Events::listen(Facility::Time, &queue);
	Events::listen(Facility::Input, &queue);

	lv_obj_add_event_cb(main, [](lv_event_t* evt){
		auto scr = static_cast<LockScreen*>(evt->user_data);
		scr->locker->stop();
	}, LV_EVENT_DEFOCUSED, this);

	lv_obj_add_event_cb(main, [](lv_event_t* evt){
		auto scr = static_cast<LockScreen*>(evt->user_data);
		scr->locker->activity();
	}, LV_EVENT_FOCUSED, this);
}

LockScreen::~LockScreen(){
	Events::unlisten(&queue);
}

void LockScreen::onStarting(){
	lv_obj_scroll_to(rest, 0, 0, LV_ANIM_OFF);
	lv_obj_scroll_to(*this, 0, 0, LV_ANIM_OFF);
	lv_group_focus_obj(main);

	for(const auto& notif : notifs){
		notifRem(notif.first);
	}

	for(const auto& notif : phone.getNotifs()){
		if(notifs.count(notif.uid) != 0){
			notifAdd(notif);
		}
	}

	updateTime(ts.getTime());
}

void LockScreen::loop(){
	locker->loop();
	if(locker->t() >= 1){
		locker->loop();
		transition([](){ return std::make_unique<MainMenu>(); });
		return;
	}

	status->loop();

	if(millis() - lastTimeUpdate > TimeUpdateInterval){
		updateTime(ts.getTime());
	}

	Event evt;
	if(queue.get(evt, 0)){
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
	if(lv_group_get_focused(inputGroup) != main) return;

	if(evt.btn == Input::Alt){
		if(evt.action == Input::Data::Press){
			if(millis() - wakeTime <= 200){
				wakeTime = 0;
				return;
			}

			locker->start();
			altPress = millis();
		}else if(evt.action == Input::Data::Release){
			locker->stop();

			if(altPress != 0 && millis() - altPress < 200){
				altPress = 0;

				auto sleep = (Sleep*) Services.get(Service::Sleep);
				sleep->sleep([this](){
					locker->hide();
					status->loop();
					updateTime(ts.getTime());
					// TODO: process all (Phone) events
					// TODO: separate queue for Phone events, so that Time and Input event queues can be reset on wake
					// TODO: trigger a single LVGL timer tick, so the screen gets pushed to display before backlight comes on
				});

				wakeTime = millis();
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

void LockScreen::notifAdd(const Notif& notif){
	// TODO: check more icons than fit in single row
	// TODO: dynamically load needed icons into cache

	if(notifs.count(notif.uid) == 0){
		lv_obj_t* icon = lv_img_create(icons);

		auto uid = notif.uid;
		auto item = std::make_unique<Item>(rest, [this, uid](){
			notifRem(uid);
			phone.doNeg(uid);
		});
		lv_group_add_obj(inputGroup, *item);
		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
		lv_obj_add_flag(*item, LV_OBJ_FLAG_SCROLL_CHAIN_VER);

		notifs.insert(std::make_pair(notif.uid, NotifEl{
				.notif = notif,
				.icon = icon,
				.item = std::move(item)
		}));
	}else{
		notifs[notif.uid].notif = notif;
	}

	NotifEl& el = notifs[notif.uid];

	lv_img_set_src(el.icon, iconPath(notif));
	el.item->update(notif);
}

void LockScreen::notifRem(uint32_t id){
	auto it = notifs.find(id);
	if(it == notifs.end()) return;
	auto& el = it->second;

	lv_group_focus_next(inputGroup);
	lv_obj_del(el.icon);
	notifs.erase(it);
}

void LockScreen::notifsClear(){
	notifs.clear(); // This has to precede rest clearing
	lv_obj_clean(rest);
	lv_obj_clean(icons);
}

void LockScreen::updateTime(const tm& time){
	lastTimeUpdate = millis();

	char clockText[128];
	char dateText[128];

	static const char* Months[] = { "January", "February", "March", "April", "May", "June", "July", "August", "September", "October", "November", "December" };
	const int dayLd = time.tm_mday - (time.tm_mday / 10) * 10;
	const char* daySuff;
	if(time.tm_mday == 11 || time.tm_mday == 12) daySuff = "th";
	else if(dayLd == 1) daySuff = "st";
	else if(dayLd == 2) daySuff = "nd";
	else if(dayLd == 3) daySuff = "rd";
	else daySuff = "th";

	snprintf(clockText, sizeof(clockText), "%02d%c%02d", time.tm_hour, time.tm_sec % 2 ? ':' : ' ', time.tm_min);
	snprintf(dateText, sizeof(dateText), "%s %d%s, %d", Months[time.tm_mon % 12], time.tm_mday, daySuff, 1900 + time.tm_year);

	lv_label_set_text(clock, clockText);
	lv_label_set_text(date, dateText);
}

void LockScreen::buildUI(){
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);

	bg = lv_obj_create(*this);
	lv_obj_add_flag(bg, LV_OBJ_FLAG_IGNORE_LAYOUT);
	lv_obj_set_size(bg, 128, 256);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_style_bg_color(bg, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(bg, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(bg, "S:/bg.bin", 0);

	main = lv_obj_create(*this);
	lv_obj_set_size(main, 128, 128);
	lv_obj_set_flex_flow(main, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(main, LV_FLEX_ALIGN_SPACE_BETWEEN, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);

	status = new StatusBar(main, false);

	mainMid = lv_obj_create(main);
	lv_obj_set_size(mainMid, 128, LV_SIZE_CONTENT);
	lv_obj_set_flex_flow(mainMid, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(mainMid, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_gap(mainMid, 2, 0);

	locker = new Slider(main);

	clock = lv_label_create(mainMid);
	lv_obj_set_style_text_align(clock, LV_TEXT_ALIGN_CENTER, 0);
	lv_obj_set_style_text_font(clock, &clockfont, 0);
	lv_obj_set_style_text_color(clock, lv_color_make(244, 126, 27), 0);

	date = lv_label_create(mainMid);
	lv_obj_set_size(date, 128, 10);
	lv_obj_set_style_text_align(date, LV_TEXT_ALIGN_CENTER, 0);

	icons = lv_obj_create(mainMid);
	lv_obj_set_size(icons, 128, 11);
	lv_obj_set_style_min_height(icons, 1, 0);
	lv_obj_set_flex_flow(icons, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(icons, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_gap(icons, 2, 0);

	rest = lv_obj_create(*this);
	lv_obj_set_size(rest, 128, 128);
	lv_obj_set_flex_flow(rest, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(rest, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_hor(rest, 4, 0);
	lv_obj_set_style_pad_ver(rest, 3, 0);
	lv_obj_set_style_pad_gap(rest, 3, 0);

	// Scrolling

	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLL_ONE);
	lv_obj_set_scroll_snap_y(*this, LV_SCROLL_SNAP_START);
	lv_obj_add_flag(main, LV_OBJ_FLAG_SNAPPABLE);
	lv_obj_add_flag(rest, LV_OBJ_FLAG_SNAPPABLE);

	lv_group_add_obj(inputGroup, main);
	lv_group_set_wrap(inputGroup, false);
	lv_obj_add_flag(main, LV_OBJ_FLAG_SCROLL_ON_FOCUS);
	lv_obj_clear_flag(main, LV_OBJ_FLAG_SCROLLABLE);
}
