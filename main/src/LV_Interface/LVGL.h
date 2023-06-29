#ifndef CLOCKSTAR_FIRMWARE_LVGL_H
#define CLOCKSTAR_FIRMWARE_LVGL_H


#include "Devices/Display.h"
#include "Util/Threaded.h"
#include <hal/lv_hal_disp.h>

class LVGL : public Threaded {
public:
	LVGL(Display& display);
	virtual ~LVGL();

	lv_disp_t* disp() const;

private:
	Display& display;

	static constexpr uint8_t Rows = 32;
	uint8_t drawBuffer[2*128*Rows];

	lv_disp_draw_buf_t lvDrawBuf;
	lv_disp_drv_t lvDispDrv;
	lv_disp_t* lvDisplay;

	static void flush(lv_disp_drv_t* dispDrv, const lv_area_t* area, lv_color_t* pixels);

	void loop() override;

};


#endif //CLOCKSTAR_FIRMWARE_LVGL_H
