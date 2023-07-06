#include "ClockLabelSmall.h"
#include "Theme/theme.h"

ClockLabelSmall::ClockLabelSmall(lv_obj_t* parent) : ClockLabel(parent){
	clock = lv_label_create(obj);
	lv_obj_set_style_text_font(clock, &devin2, 0);

	updateTime(ts.getTime());
}

void ClockLabelSmall::updateUI(const char* clockText){
	lv_label_set_text(clock, clockText);
}
