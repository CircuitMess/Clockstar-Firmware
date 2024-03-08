#ifndef CLOCKSTAR_FIRMWARE_BATTERYELEMENT_H
#define CLOCKSTAR_FIRMWARE_BATTERYELEMENT_H

#include "LV_Interface/LVObject.h"
#include "Filepaths.hpp"
#include "Devices/Battery.h"
#include "Util/Events.h"
#include "Settings/Settings.h"

class BatteryElement : public LVObject {
public:
	BatteryElement(lv_obj_t* parent);
	~BatteryElement() override;

	void loop();

	virtual void updateVisuals() override;

private:
	enum Level {
		Empty, Low, Mid, Full, Charging
	};

	lv_obj_t* img;
	Level level = Full;
	Battery& battery;
	EventQueue queue;

	uint8_t chargingIndex = 0;
	static constexpr uint32_t ChargingAnimTime = 500;
	static constexpr uint8_t BatteryLevels = 4;
	uint32_t chargingMillis = 0;

	void set(Level level);
};


#endif //CLOCKSTAR_FIRMWARE_BATTERYELEMENT_H
