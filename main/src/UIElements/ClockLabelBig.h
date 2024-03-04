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
			File::Clock::Theme1::Num0,
			File::Clock::Theme1::Num1,
			File::Clock::Theme1::Num2,
			File::Clock::Theme1::Num3,
			File::Clock::Theme1::Num4,
			File::Clock::Theme1::Num5,
			File::Clock::Theme1::Num6,
			File::Clock::Theme1::Num7,
			File::Clock::Theme1::Num8,
			File::Clock::Theme1::Num9,
			File::Clock::Theme1::Colon,
			File::Clock::Theme1::Space
	};
};


#endif //CLOCKSTAR_FIRMWARE_CLOCKLABELBIG_H
