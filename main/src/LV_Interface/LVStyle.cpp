#include "LVStyle.h"

LVStyle::LVStyle(){
	lv_style_init(&style);
}

LVStyle::operator lv_style_t*(){
	return &style;
}

LVStyle::~LVStyle(){
	lv_style_reset(&style);
}
