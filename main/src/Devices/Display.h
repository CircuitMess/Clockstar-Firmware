#ifndef CLOCKSTAR_FIRMWARE_DISPLAY_H
#define CLOCKSTAR_FIRMWARE_DISPLAY_H

#include <LovyanGFX.h>

class Display {
public:
	Display();
	virtual ~Display();

	void drawTest();

private:
	lgfx::Bus_SPI bus;
	lgfx::Panel_ST7735S panel;
	LGFX_Device lgfx;

	void setupBus();
	void setupPanel();

};


#endif //CLOCKSTAR_FIRMWARE_DISPLAY_H
