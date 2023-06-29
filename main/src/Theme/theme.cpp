#include <cstdio>
#include "theme.h"

static lv_theme_t theme;

static struct {
	lv_style_t label;
} styles;

static void theme_apply(lv_theme_t* th, lv_obj_t* obj){
	if(lv_obj_check_type(obj, &lv_label_class)) {
		lv_obj_add_style(obj, &styles.label, 0);
	}
}

lv_theme_t* theme_init(lv_disp_t* disp){
	lv_style_init(&styles.label);
	lv_style_set_text_font(&styles.label, &devin);

	memset(&theme, 0, sizeof(lv_theme_t));
	theme.apply_cb = theme_apply;
	theme.parent = lv_disp_get_theme(disp);
	theme.disp = disp;
	theme.color_primary = lv_color_make(244, 126, 27);
	theme.color_secondary = lv_color_make(207, 198, 184);
	theme.font_small = &devin;
	theme.font_normal = &devin;
	theme.font_large = &clockfont;
	return &theme;
}
