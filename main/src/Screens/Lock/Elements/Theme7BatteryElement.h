#ifndef ARTEMIS_FIRMWARE_THEME7BATTERYELEMENT_H
#define ARTEMIS_FIRMWARE_THEME7BATTERYELEMENT_H

#include "UIElements/BatteryElement.h"

class Theme7BatteryElement : public BatteryElement {
public:
	explicit Theme7BatteryElement(lv_obj_t* parent);

protected:
	virtual void updateChargingVisuals() override;
	virtual void updateLevelVisuals() override;
};

#endif //ARTEMIS_FIRMWARE_THEME7BATTERYELEMENT_H