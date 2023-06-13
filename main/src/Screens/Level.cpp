#include <algorithm>
#include "Level.h"
#include <cmath>
#include <glm/glm/vec2.hpp>
#include <glm/glm/geometric.hpp>

Level::Level(){
	bg = lv_obj_create(*this);
	lv_obj_set_pos(bg, 0, 0);
	lv_obj_set_size(bg, 128, 128);
	lv_obj_set_style_bg_img_src(bg, "S:/level/bg.bin", LV_STATE_DEFAULT);

	bubbleCenter = lv_img_create(bg);
	lv_img_set_src(bubbleCenter, "S:/level/bubbleCenter.bin");
	bubbleHorizontal = lv_img_create(bg);
	lv_img_set_src(bubbleHorizontal, "S:/level/bubbleHorizontal.bin");
	lv_obj_set_y(bubbleHorizontal, 103);
	bubbleVertical = lv_img_create(bg);
	lv_img_set_src(bubbleVertical, "S:/level/bubbleVertical.bin");
	lv_obj_set_x(bubbleVertical, 102);


	markingsCenter = lv_img_create(bg);
	lv_img_set_src(markingsCenter, "S:/level/markingsCenter.bin");
	lv_obj_set_pos(markingsCenter, 12, 12);
	markingsHorizontal = lv_img_create(bg);
	lv_img_set_src(markingsHorizontal, "S:/level/markingsHorizontal.bin");
	lv_obj_set_pos(markingsHorizontal, 34, 100);
	markingsVertical = lv_img_create(bg);
	lv_img_set_src(markingsVertical, "S:/level/markingsVertical.bin");
	lv_obj_set_pos(markingsVertical, 99, 34);

	setOrientation(0, 0);
}

void Level::setOrientation(float pitch, float roll){
	pitch = std::clamp(pitch, -AngleConstraint, AngleConstraint);
	roll = std::clamp(roll, -AngleConstraint, AngleConstraint);

	const auto horizontalX = (int16_t) (((roll + AngleConstraint) / (2 * AngleConstraint)) * (HorizontalConstr.max - HorizontalConstr.min) +
										HorizontalConstr.min);
	const auto verticalY = (int16_t) (((pitch + AngleConstraint) / (2 * AngleConstraint)) * (VerticalConstr.max - VerticalConstr.min) + VerticalConstr.min);

	const glm::vec2 vec = { roll / AngleConstraint, pitch / AngleConstraint };
	auto centerVec = vec * (float) CenterConstr;
	if(glm::length(centerVec) > CenterConstr){
		centerVec *= (CenterConstr / glm::length(centerVec));
	}

	lv_obj_set_pos(bubbleCenter, (int16_t) (CenterPos + centerVec.x), (int16_t) (CenterPos + centerVec.y));
	lv_obj_set_x(bubbleHorizontal, horizontalX);
	lv_obj_set_y(bubbleVertical, verticalY);

}
