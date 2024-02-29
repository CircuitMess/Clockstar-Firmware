#ifndef ARTEMIS_FIRMWARE_INTROSCREEN_H
#define ARTEMIS_FIRMWARE_INTROSCREEN_H

#include "LV_Interface/LVScreen.h"
#include "Filepaths.hpp"

class IntroScreen : public LVScreen {
public:
	IntroScreen();
private:
	void onStop() override;
private:
	void onStart() override;
	void loop() override;
	lv_obj_t* bg;
	lv_obj_t* imageConts[3];
	lv_obj_t* images[3];
	static constexpr const char* ImagePaths[3] = {
			File::Intro::GeekClub, File::Intro::CircuitMess, File::Intro::Space
	};

	static constexpr uint32_t ScrollTime = 500;
	static constexpr uint32_t WaitTime = 1000;
	static constexpr uint32_t InitialWaitTime = 2000;

	enum {
		Scrolling, Waiting
	} state = Waiting;
	uint32_t counter = 0;

	int8_t currentIndex = -1;
	lv_anim_t anim;

	static void animFunc(void *, int32_t);
};


#endif //ARTEMIS_FIRMWARE_INTROSCREEN_H
