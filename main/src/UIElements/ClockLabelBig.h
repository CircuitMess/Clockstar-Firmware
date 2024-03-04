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

	static constexpr const char* getPath(char c);

	static constexpr uint8_t NumIcons = 5;
	lv_obj_t* icons[NumIcons]{};

	static constexpr const char* IconPaths[12] = {
			File::Clock::Default::Num0,
			File::Clock::Default::Num1,
			File::Clock::Default::Num2,
			File::Clock::Default::Num3,
			File::Clock::Default::Num4,
			File::Clock::Default::Num5,
			File::Clock::Default::Num6,
			File::Clock::Default::Num7,
			File::Clock::Default::Num8,
			File::Clock::Default::Num9,
			File::Clock::Default::Colon,
			File::Clock::Default::Space
	};
};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H
