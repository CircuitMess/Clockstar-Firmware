#ifndef CLOCKSTAR_FIRMWARE_BATTERYELEMENT_H
#define CLOCKSTAR_FIRMWARE_BATTERYELEMENT_H


#include "LV_Interface/LVObject.h"

class BatteryElement : public LVObject {
public:
	enum Level {
		Empty, Low, Mid, Full, Charging
	};

	BatteryElement(lv_obj_t* parent);
	void set(Level level);
	[[nodiscard]] Level getLevel() const;

	void loop();

private:
	lv_obj_t* img;
	Level level = Full;

	uint8_t chargingIndex = 0;
	static constexpr uint32_t ChargingAnimTime = 500;
	static constexpr uint8_t BatteryLevels = 3;
	uint32_t chargingMillis = 0;

	static constexpr uint32_t LowBatteryAnimTime = 500;
	bool lowBatteryAnimToggle = false;
	uint32_t lowBatMillis = 0;

	static constexpr const char* BatteryIcons[] = { "S:/icons/batteryLow.bin", "S:/icons/batteryMid.bin", "S:/icons/batteryFull.bin" };
};


#endif //CLOCKSTAR_FIRMWARE_BATTERYELEMENT_H
