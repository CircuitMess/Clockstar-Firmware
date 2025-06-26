#include "Pins.hpp"
#include "Util/EfuseMeta.h"

static const char* TAG = "Pins";

int Pins::get(Pin pin){
	if(instance == nullptr){
		instance = new Pins();
		uint8_t revision = 0;
		EfuseMeta::readRev(revision);

		if(revision == 0 || revision == 1){
			instance->currentMap = &instance->Revision1;
		}else if(revision == 2){
			instance->currentMap = &instance->Revision2;
		}else{
			while(true){
				EfuseMeta::log();
				while(true);
			}
		}
	}

	assert(instance != nullptr);

	PinMap* pinMap = instance->currentMap;

	if(pinMap == nullptr){
		ESP_LOGE(TAG, "Pin map is invalid.!\n");
		return -1;
	}

	if(!pinMap->contains(pin)){
		ESP_LOGE(TAG, "Pin %d not mapped!\n", (int) pin);
		return -1;
	}

	return pinMap->at(pin);
}

void Pins::setLatest(){
	if(instance == nullptr){
		instance = new Pins();
	}

	instance->currentMap = instance->pinMaps.back();
}

Pins::Pins(){
	initPinMaps();
}

void Pins::initPinMaps(){
	Revision1 = {
			{ Pin::BtnDown,   14 },
			{ Pin::BtnUp,     15 },
			{ Pin::BtnSelect, 27 },
			{ Pin::BtnAlt,    39 },
			{ Pin::LedBl,     4 },
			{ Pin::Buzz,      2 },
			{ Pin::BattRead,  36 },
			{ Pin::BattVref,  -1 },
			{ Pin::Usb,       19 },
			{ Pin::I2cSda,    26 },
			{ Pin::I2cScl,    25 },
			{ Pin::TftSck,    16 },
			{ Pin::TftMosi,   17 },
			{ Pin::TftDc,     5 },
			{ Pin::TftRst,    18 },
			{ Pin::Rgb_r,     21 },
			{ Pin::Rgb_g,     22 },
			{ Pin::Rgb_b,     23 },
			{ Pin::Imu_int1,  35 },
			{ Pin::Imu_int2,  34 },
	};

	Revision2 = {
			{ Pin::BtnDown,   40 },
			{ Pin::BtnUp,     38 },
			{ Pin::BtnSelect, 39 },
			{ Pin::BtnAlt,    37 },
			{ Pin::LedBl,     9 },
			{ Pin::Buzz,      11 },
			{ Pin::BattRead,  10 },
			{ Pin::BattVref,  35 },
			{ Pin::Usb,       36 },
			{ Pin::I2cSda,    4 },
			{ Pin::I2cScl,    5 },
			{ Pin::TftSck,    48 },
			{ Pin::TftMosi,   34 },
			{ Pin::TftDc,     33 },
			{ Pin::TftRst,    47 },
			{ Pin::Rgb_r,     8 },
			{ Pin::Rgb_g,     7 },
			{ Pin::Rgb_b,     6 },
			{ Pin::Imu_int1,  41 },
			{ Pin::Imu_int2,  42 },
	};
}

