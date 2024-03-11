#ifndef ARTEMIS_FIRMWARE_THEME8BATTERYELEMENT_H
#define ARTEMIS_FIRMWARE_THEME8BATTERYELEMENT_H

#include "UIElements/BatteryElement.h"

class Theme8BatteryElement : public BatteryElement {
public:
	explicit Theme8BatteryElement(lv_obj_t* parent);

protected:
	virtual void updateChargingVisuals() override;
	virtual void updateLevelVisuals() override;
};

#endif //ARTEMIS_FIRMWARE_THEME8BATTERYELEMENT_H