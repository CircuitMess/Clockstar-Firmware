#include "LockSkin.h"

LockSkin::LockSkin(lv_obj_t* parent, lv_group_t* inputGroup) : LVObject(parent), inputGroup(inputGroup){
	buildUI();
}

LockSkin::~LockSkin(){
	delete status;
	delete clock;
	delete locker;

	status = nullptr;
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

	if(status != nullptr){
		status->loop();
	}

	if(clock != nullptr){
		clock->loop();
	}
}

void LockSkin::prepare(){
	lv_obj_scroll_to(rest, 0, 0, LV_ANIM_OFF);
	lv_obj_scroll_to(*this, 0, 0, LV_ANIM_OFF);
	lv_group_focus_obj(main);

	if(locker != nullptr){
		locker->hide();
	}

	if(status != nullptr){
		status->loop();
	}

	if(clock != nullptr){
		clock->loop();
	}
}

void LockSkin::buildUI(){
	lv_obj_add_flag(*this, LV_OBJ_FLAG_SCROLLABLE);
	lv_obj_set_flex_flow(*this, LV_FLEX_FLOW_COLUMN);

	main = lv_obj_create(*this);
	if(main == nullptr){
		return;
	}

	static const lv_coord_t col_dsc[] = { 128, LV_GRID_TEMPLATE_LAST };
	static const lv_coord_t row_dsc[] = { 15, 17, 50, 29, 17, LV_GRID_TEMPLATE_LAST };
	lv_obj_set_style_grid_column_dsc_array(main, col_dsc, 0);
	lv_obj_set_style_grid_row_dsc_array(main, row_dsc, 0);
	lv_obj_set_size(main, 128, 128);
	lv_obj_set_layout(main, LV_LAYOUT_GRID);

	status = new StatusBar(main, false);
	lv_obj_set_grid_cell(status->operator lv_obj_t*(), LV_GRID_ALIGN_STRETCH, 0, 1, LV_GRID_ALIGN_STRETCH, 0, 1);

	clock = new ClockLabelBig(main);
	lv_obj_set_grid_cell(clock->operator lv_obj_t*(), LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 2, 1);

	icons = lv_obj_create(main);
	if(icons == nullptr){
		return;
	}

	lv_obj_set_size(icons, 128, 11);
	lv_obj_set_style_min_height(icons, 1, 0);
	lv_obj_set_flex_flow(icons, LV_FLEX_FLOW_ROW);
	lv_obj_set_flex_align(icons, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER, LV_FLEX_ALIGN_CENTER);
	lv_obj_set_style_pad_gap(icons, 2, 0);
	lv_obj_set_grid_cell(icons, LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 3, 1);

	locker = new Slider(main);
	lv_obj_set_grid_cell(locker->operator lv_obj_t*(), LV_GRID_ALIGN_CENTER, 0, 1, LV_GRID_ALIGN_CENTER, 4, 1);

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
	lv_obj_set_style_bg_img_src(main, "S:/lockbg.bin", 0);

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
