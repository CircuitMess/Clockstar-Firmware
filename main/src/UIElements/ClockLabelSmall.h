#ifndef CLOCKSTAR_FIRMWARE_CLOCKLABELSMALL_H
#define CLOCKSTAR_FIRMWARE_CLOCKLABELSMALL_H

#include "ClockLabel.h"

class ClockLabelSmall : public ClockLabel {
public:
	explicit ClockLabelSmall(lv_obj_t* parent);

private:
	void updateUI(const char* clockText) override;
	lv_obj_t* clock;
};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABELSMALL_H
