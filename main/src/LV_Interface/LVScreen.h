#ifndef BATCONTROLLER_FIRMWARE_LVSCREEN_H
#define BATCONTROLLER_FIRMWARE_LVSCREEN_H

#include <lvgl.h>
#include "LVObject.h"
#include <unordered_set>

class LVGL;

class LVScreen : public LVObject {
public:
	LVScreen();
	virtual ~LVScreen();

	virtual void onStarting();
	virtual void onStart();
	virtual void onStop();

	void start(bool animate = false, lv_scr_load_anim_t animation = LV_SCR_LOAD_ANIM_MOVE_BOTTOM);
	void stop();

	void push(LVScreen* other);
	void pop();

	lv_group_t* getInputGroup();

	void setParent(LVScreen* parent);
	LVScreen* getParent() const;

	static LVScreen* getCurrent();

	bool isRunning() const;

protected:
	lv_group_t* inputGroup;

	LVScreen* parent = nullptr;

private:
	static LVScreen* current;
	std::unordered_set<LVScreen*> delOnStart;

	bool running = false;

	friend LVGL;
	virtual void loop();

};


#endif //BATCONTROLLER_FIRMWARE_LVSCREEN_H
