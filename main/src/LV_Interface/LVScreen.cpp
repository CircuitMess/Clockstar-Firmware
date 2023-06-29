#include "LVScreen.h"
#include "InputLVGL.h"
#include <cstdio>

LVScreen* LVScreen::current = nullptr;

LVScreen::LVScreen() : LVObject(nullptr){
	delOnStart.reserve(4);

	lv_obj_add_event_cb(obj, [](lv_event_t* event){
		auto screen = static_cast<LVScreen*>(event->user_data);

		// LoopManager::defer([screen](uint32_t){ TODO: check if this is necessary since it should only be invoked from UI thread
			lv_indev_set_group(InputLVGL::getInstance()->getIndev(), screen->inputGroup);

			for(auto del : screen->delOnStart){
				lv_obj_del((lv_obj_t*)del);
			}
			screen->delOnStart.clear();

			lv_timer_handler();
			screen->onStart();
		// });
	}, LV_EVENT_SCREEN_LOADED, this);

	inputGroup = lv_group_create();
}

LVScreen::~LVScreen(){
	if(running){
		printf("LVScreen: destroying while still running! Call stop() first.\n");
		abort();
		return;
	}
	lv_group_del(inputGroup);

	if(current == this){
		current = nullptr;
	}
}

lv_group_t* LVScreen::getInputGroup(){
	return inputGroup;
}

void LVScreen::start(bool animate, lv_scr_load_anim_t anim){
	if(running) return;

	onStarting();

	running = true;
	current = this;

	if(animate){
		// LoopManager::defer([this, anim](uint32_t){ TODO: check if this is necessary since it should only be invoked from UI thread
			lv_scr_load_anim(obj, anim, 500, 0, false);
		// });
	}else{
		lv_scr_load(obj);
	}
}

void LVScreen::stop(){
	if(!running) return;
	running = false;
	// lv_indev_set_group(InputLVGL::getInstance()->getIndev(), nullptr);
	onStop();
}

void LVScreen::push(LVScreen* other){
	other->parent = this;
	stop();
	other->start(true, LV_SCR_LOAD_ANIM_FADE_ON);
}

void LVScreen::pop(){
	if(parent == nullptr) return;

	stop();

	parent->delOnStart.insert(this);
	parent->start(true, LV_SCR_LOAD_ANIM_FADE_ON);
}

void LVScreen::setParent(LVScreen* parent){
	LVScreen::parent = parent;
}

LVScreen* LVScreen::getParent() const{
	return parent;
}

void LVScreen::onStarting(){ }

void LVScreen::onStart(){ }

void LVScreen::onStop(){ }

void LVScreen::loop(){ }

LVScreen* LVScreen::getCurrent(){
	return current;
}

bool LVScreen::isRunning() const{
	return running;
}
