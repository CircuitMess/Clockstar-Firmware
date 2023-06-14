#ifndef CLOCKSTAR_FIRMWARE_THEREMIN_H
#define CLOCKSTAR_FIRMWARE_THEREMIN_H

#include "../LV_Interface/LVScreen.h"
#include "../LV_Interface/LVStyle.h"

class Theremin : public LVScreen {
public:
	Theremin();
	void setOrientation(float pitch, float roll);

private:
	lv_obj_t* bg;
	lv_obj_t* textVertical, * textHorizontal;
	lv_obj_t* sliderVertical, * sliderHorizontal;

	static constexpr float AngleConstraint = 45.0f;
	static constexpr uint8_t SliderLength = 104;
	static constexpr uint8_t SliderWidth = 12;
	static constexpr uint8_t SliderRange = 95;


	static constexpr uint8_t VerticalBarX = 5;
	static constexpr uint8_t VerticalBarY = 5;
	static constexpr uint8_t VerticalTextX = 24;
	static constexpr uint8_t VerticalTextY = 9;

	static constexpr uint8_t HorizontalBarX = 18;
	static constexpr uint8_t HorizontalBarY = 110;
	static constexpr uint8_t HorizontalTextX = 23;
	static constexpr uint8_t HorizontalTextY = 75;
	LVStyle textStyle;
};


#endif //CLOCKSTAR_FIRMWARE_THEREMIN_H
