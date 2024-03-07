#ifndef CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H
#define CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H

#include "ClockLabel.h"
#include "Filepaths.hpp"

class ClockLabelBig : public ClockLabel {
public:
	explicit ClockLabelBig(lv_obj_t* parent);
	~ClockLabelBig() override = default;
private:
	void updateUI(const char* clockText, const char* ps) override;

	static const char* getPath(char c);

	static constexpr uint8_t NumIcons = 5;
	lv_obj_t* icons[NumIcons]{};
};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H
