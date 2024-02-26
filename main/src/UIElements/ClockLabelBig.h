#ifndef CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H
#define CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H

#include "ClockLabel.h"

class ClockLabelBig : public ClockLabel {
public:
	explicit ClockLabelBig(lv_obj_t* parent);
	~ClockLabelBig() override = default;
private:
	void updateUI(const char* clockText) override;


	static constexpr const char* getPath(char c);

	static constexpr uint8_t NumIcons = 5;
	lv_obj_t* icons[NumIcons]{};

	static constexpr const char* IconPaths[12] = {
			"S:/default/clock/0.bin", "S:/default/clock/1.bin", "S:/default/clock/2.bin", "S:/default/clock/3.bin", "S:/default/clock/4.bin", "S:/default/clock/5.bin",
			"S:/default/clock/6.bin", "S:/default/clock/7.bin", "S:/default/clock/8.bin", "S:/default/clock/9.bin", "S:/default/clock/colon.bin", "S:/default/clock/space.bin"
	};
};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H
