#ifndef CLOCKSTAR_FIRMWARE_LEVEL_H
#define CLOCKSTAR_FIRMWARE_LEVEL_H

#include "../LV_Interface/LVScreen.h"
#include "../LV_Interface/LVStyle.h"
#include <lvgl.h>

class Level : public LVScreen {
public:
	Level();
	void setOrientation(float pitch, float roll);

private:
	lv_obj_t* bg;
	lv_obj_t* markingsHorizontal, * markingsCenter, * markingsVertical;
	lv_obj_t* bubbleHorizontal, * bubbleCenter, * bubbleVertical;

	struct Constraint {
		uint8_t min;
		uint8_t max;
	};

	static constexpr Constraint VerticalConstr = { 10, 73 };
	static constexpr Constraint HorizontalConstr = { 10, 72 };
	static constexpr int8_t CenterConstr = 27;
	static constexpr int8_t CenterPos = 40;
	static constexpr float AngleConstraint = 45.0f;

};

#endif //CLOCKSTAR_FIRMWARE_LEVEL_H
