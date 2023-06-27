#include "LVGL.h"
#include <lvgl.h>
#include "LVScreen.h"

LVGL::LVGL(Display& display) : Threaded("LVGL", 12 * 1024, 6, 1), display(display){
	lv_init();
	lv_disp_draw_buf_init(&lvDrawBuf, drawBuffer, nullptr, sizeof(drawBuffer) / 2);

	lv_disp_drv_init(&lvDispDrv);
	lvDispDrv.hor_res = 128;
	lvDispDrv.ver_res = 128;
	lvDispDrv.flush_cb = flush;
	lvDispDrv.draw_buf = &lvDrawBuf;
	lvDispDrv.user_data = this;
	lvDisplay = lv_disp_drv_register(&lvDispDrv);
}

LVGL::~LVGL(){
	stop();
}

void LVGL::flush(lv_disp_drv_t* dispDrv, const lv_area_t* area, lv_color_t* pixels){
	auto lvgl = static_cast<LVGL*>(dispDrv->user_data);
	auto lgfx = lvgl->display.getLGFX();

	auto x = area->x1;
	auto y = area->y1;
	auto w = (area->x2 - area->x1 + 1);
	auto h = (area->y2 - area->y1 + 1);
	auto data = &pixels->full;

	lgfx.pushImage(x, y, w, h, data);

	lv_disp_flush_ready(dispDrv);
}

void LVGL::loop(){
	auto scr = LVScreen::getCurrent();
	if(scr != nullptr){
		scr->loop();
	}

	auto ttn = lv_timer_handler();
	if(ttn <= 0 || ttn > LV_DISP_DEF_REFR_PERIOD) ttn = 1;
	vTaskDelay(ttn);
}
