#ifndef ARTEMIS_FIRMWARE_LOADINGMODAL_H
#define ARTEMIS_FIRMWARE_LOADINGMODAL_H

#include "LV_Interface/LVModal.h"
#include "LabelElement.h"

class LoadingModal : public LVModal {
public:
	explicit LoadingModal(LVScreen* parent);

private:
	LabelElement* text;
};

#endif //ARTEMIS_FIRMWARE_LOADINGMODAL_H