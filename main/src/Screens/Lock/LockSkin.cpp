#include "LockSkin.h"
#include "Filepaths.hpp"
#include "Settings/Settings.h"
#include "Util/Services.h"
#include "LV_Interface/InputLVGL.h"

LockSkin::LockSkin(lv_obj_t* parent, lv_group_t* inputGroup) : LVObject(parent), inputGroup(inputGroup){
	notifs.reserve(MaxNotifs);
	notifIcons.reserve(MaxIconsCount);
}

LockSkin::~LockSkin(){
	//delete status;
	delete clock;
	delete locker;

	//status = nullptr;
	clock = nullptr;
	locker = nullptr;
}

void LockSkin::loop(){
	if(locker != nullptr){
		locker->loop();
		if(locker->t() >= 1){
			locker->loop();
			return;
		}
	}

	if(phoneElement != nullptr){
		phoneElement->loop();
	}

	if(batteryElement != nullptr){
		batteryElement->loop();
	}

	if(clock != nullptr){
		clock->loop();
	}
}

void LockSkin::prepare(){
	buildUI();

	lv_obj_scroll_to(rest, 0, 0, LV_ANIM_OFF);
	lv_obj_scroll_to(*this, 0, 0, LV_ANIM_OFF);
	lv_group_focus_obj(main);

	if(locker != nullptr){
		locker->hide();
	}

	if(phoneElement != nullptr){
		phoneElement->loop();
	}

	if(batteryElement != nullptr){
		batteryElement->loop();
	}

	if(clock != nullptr){
		clock->loop();
	}

	updateNotifs();
}

void LockSkin::notifAdd(const Notif& notif){
	bool isModify = true;

	if(notifs.count(notif.uid) == 0){
		if(notifs.size() >= MaxNotifs) return;

		isModify = false;

		auto uid = notif.uid;
		auto item = new Item(rest, [this, uid](){
			notifRem(uid);

			if(Phone* phone = (Phone*) Services.get(Service::Phone)){
				phone->doNeg(uid);
			}
		});

		bool itemActive = false;
		if(InputLVGL::getInstance()->getIndev()->group != inputGroup){
			itemActive = true;
		}

		auto focused = lv_group_get_focused(inputGroup);
		lv_obj_move_to_index(*item, 0);
		lv_group_remove_all_objs(inputGroup);
		lv_group_add_obj(inputGroup, getMain());
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
	el->update(notif);
}

void LockSkin::notifRem(uint32_t id){
	auto it = notifs.find(id);
	if(it == notifs.end()) return;
	auto& el = it->second;

	removeNotifIcon(el->iconPath());
	lv_group_focus_next(inputGroup);

	lv_obj_del(*el);
	notifs.erase(it);
}

void LockSkin::notifsClear(){
	notifs.clear(); // This has to precede rest clearing
	lv_obj_clean(rest);

	notifIcons.clear();
	lv_obj_clean(icons);
}

void LockSkin::addNotifIcon(const char* path){
	if(path == nullptr) return;

	if(notifIcons.count(path)){
		notifIcons[path].count++;
		return;
	}

	if(notifIcons.size() >= MaxIconsCount) return;


	lv_obj_t* icon = lv_img_create(icons);
	lv_img_set_src(icon, path);

	NotifIcon notifIcon = { 1, icon };
	notifIcons.insert({ path, notifIcon });
}

void LockSkin::removeNotifIcon(const char* path){
	if(path == nullptr) return;

	auto pair = notifIcons.find(path);
	if(pair == notifIcons.end()) return;

	pair->second.count -= 1;
	if(pair->second.count > 0) return;

	lv_obj_del(pair->second.icon);
	notifIcons.erase(pair);
}

void LockSkin::updateNotifs(){
	Phone* phone = (Phone*) Services.get(Service::Phone);
	if(phone == nullptr){
		return;
	}

	const auto set = phone->getNotifs();
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
	}
}

void LockSkin::buildUI(){
	Settings* settings = (Settings*) Services.get(Service::Settings);
	if(settings == nullptr){
		return;
	}

	const ThemeStruct themeData = settings->get().themeData;

	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);

	main = lv_obj_create(*this);
	if(main == nullptr){
		return;
	}

	lv_obj_set_size(main, 128, 128);

	batteryElement = new BatteryElement(main);
	lv_obj_set_align(*batteryElement, LV_ALIGN_CENTER);
	lv_obj_set_x(*batteryElement, themeData.batteryX);
	lv_obj_set_y(*batteryElement, themeData.batteryY);

	phoneElement = new PhoneElement(main, false);
	lv_obj_set_align(*phoneElement, LV_ALIGN_CENTER);
	lv_obj_set_x(*phoneElement, themeData.phoneX);
	lv_obj_set_y(*phoneElement, themeData.phoneY);

	clock = new ClockLabelBig(main, themeData.verticalClock, themeData.clockPadding);
	lv_obj_set_align(*clock, LV_ALIGN_CENTER);
	lv_obj_set_x(*clock, themeData.clockX);
	lv_obj_set_y(*clock, themeData.clockY);

	icons = lv_obj_create(main);
	if(icons == nullptr){
		return;
	}

	lv_obj_set_size(icons, 128, 11);
	lv_obj_set_style_min_height(icons, 1, 0);
	lv_obj_set_flex_flow(icons, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(icons, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_gap(icons, 2, 0);

	locker = new Slider(main, themeData.sliderConfig);
	lv_obj_set_y(*locker, themeData.sliderY);

	rest = lv_obj_create(*this);
	if(rest == nullptr){
		return;
	}

	lv_obj_set_size(rest, 128, 128);
	lv_obj_set_flex_flow(rest, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(rest, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_hor(rest, 4, 0);
	lv_obj_set_style_pad_ver(rest, 3, 0);
	lv_obj_set_style_pad_gap(rest, 3, 0);

	// BG

	lv_obj_set_style_bg_color(main, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(main, LV_OPA_COVER, 0);
	lv_obj_set_style_bg_img_src(main, THEMED_FILE(LockScreen, Background, themeData.theme), 0);

	lv_obj_set_style_bg_color(rest, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(rest, LV_OPA_COVER, 0);
	lv_obj_set_style_border_color(rest, lv_color_make(255, 101, 0), 0);
	lv_obj_set_style_border_opa(rest, LV_OPA_COVER, 0);
	lv_obj_set_style_border_width(rest, 1, 0);

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
