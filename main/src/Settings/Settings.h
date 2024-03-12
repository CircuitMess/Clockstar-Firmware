#ifndef CLOCKSTAR_FIRMWARE_SETTINGS_H
#define CLOCKSTAR_FIRMWARE_SETTINGS_H

#include <nvs.h>
#include "core/lv_theme.h"
#include "Screens/Lock/Slider.h"

enum class Theme : uint8_t {
	Theme1 [[maybe_unused]],
	Theme2 [[maybe_unused]],
	Theme3 [[maybe_unused]],
	Theme4 [[maybe_unused]],
	Theme5 [[maybe_unused]],
	Theme6 [[maybe_unused]],
	Theme7 [[maybe_unused]],
	Theme8 [[maybe_unused]],
	Theme9 [[maybe_unused]],
	Default [[maybe_unused]] = Theme1
};

struct ThemeStruct {
	Theme theme = Theme::Default;
	lv_color_t primaryColor = lv_color_black();
	uint8_t opacity = LV_OPA_100;
	lv_color_t textColor = lv_color_black();
	lv_color_t clockColor = lv_color_black();
	lv_color_t backgroundColor = lv_color_black();
	SliderConfig sliderConfig = {};
	lv_coord_t sliderY = 0;
	lv_coord_t clockX = 0;
	lv_coord_t clockY = 0;
	lv_coord_t batteryX = 0;
	lv_coord_t batteryY = 0;
	lv_coord_t phoneX = 0;
	lv_coord_t phoneY = 0;
	bool verticalClock = false;
	int16_t clockPadding = 0;
};

inline static ThemeStruct createTheme(Theme theme){
	ThemeStruct data = {};
	data.theme = theme;

	switch(theme){
		case Theme::Theme1:{
			data.primaryColor = lv_color_make(255, 101, 0);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(255, 101, 0);
			data.opacity = LV_OPA_100;
			data.sliderConfig.start = 6;
			data.sliderConfig.end = 122;
			data.sliderConfig.y = 3;
			data.sliderY = 111;
			data.clockY = -8;
			data.batteryX = 4;
			data.batteryY = 4;
			data.phoneX = 56;
			data.phoneY = -57;

			break;
		}
		case Theme::Theme2:{
			data.primaryColor = lv_color_make(255, 38, 116);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(255, 38, 116);
			data.opacity = LV_OPA_100;
			data.sliderConfig.start = 108;
			data.sliderConfig.end = 20;
			data.sliderConfig.y = 0;
			data.sliderY = 102;
			data.clockY = -20;
			data.batteryX = 68;
			data.batteryY = 10;
			data.phoneX = -46;
			data.phoneY = -48;

			break;
		}
		case Theme::Theme3:{
			data.primaryColor = lv_color_make(255, 255, 255);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(255, 255, 255);
			data.opacity = LV_OPA_100;
			data.sliderConfig.start = 6;
			data.sliderConfig.end = 122;
			data.sliderConfig.y = 0;
			data.sliderY = 106;
			data.clockY = -18;
			data.batteryX = 65;
			data.batteryY = 1;
			data.phoneX = -44;
			data.phoneY = -60;

			break;
		}
		case Theme::Theme4:{
			data.primaryColor = lv_color_make(38, 43, 68);
			data.textColor = lv_color_make(192, 203, 220);
			data.clockColor = lv_color_make(38, 43, 68);
			data.backgroundColor = lv_color_make(192, 203, 220);
			data.opacity = LV_OPA_100;
			data.sliderConfig.start = 122;
			data.sliderConfig.end = 8;
			data.sliderConfig.y = 3;
			data.sliderY = 109;
			data.clockX = -20;
			data.clockY = -4;
			data.verticalClock = true;
			data.batteryX = 85;
			data.batteryY = 20;
			data.phoneX = 25;
			data.phoneY = -21;

			break;
		}
		case Theme::Theme5:{
			data.primaryColor = lv_color_make(244, 180, 27);
			data.textColor = lv_color_make(244, 180, 27);
			data.clockColor = lv_color_make(244, 180, 27);
			data.backgroundColor = lv_color_make(55, 66, 99);
			data.opacity = LV_OPA_0;
			data.sliderConfig.start = 124;
			data.sliderConfig.end = 24;
			data.sliderConfig.y = 3;
			data.sliderY = 113;
			data.clockX = -26;
			data.clockY = -12;
			data.clockPadding = 6;
			data.verticalClock = true;
			data.batteryX = 118;
			data.batteryY = 20;
			data.phoneX = 42;
			data.phoneY = -5;

			break;
		}
		case Theme::Theme6:{
			data.primaryColor = lv_color_make(0, 0, 255);
			data.textColor = lv_color_make(255, 255, 0);
			data.clockColor = lv_color_make(255, 255, 255);
			data.opacity = LV_OPA_100;
			data.sliderConfig.start = 126;
			data.sliderConfig.end = 2;
			data.sliderConfig.y = 0;
			data.sliderY = 110;
			data.clockY = -30;
			data.batteryX = 110;
			data.batteryY = 1;
			data.phoneX = -56;
			data.phoneY = -57;

			break;
		}
		case Theme::Theme7:{
			data.primaryColor = lv_color_make(251, 247, 54);
			data.textColor = lv_color_make(251, 242, 54);
			data.clockColor = lv_color_make(251, 247, 54);
			data.opacity = LV_OPA_0;
			data.sliderConfig.start = 126;
			data.sliderConfig.end = 20;
			data.sliderConfig.y = 3;
			data.sliderY = 111;
			data.clockY = -4;
			data.batteryX = 92;
			data.batteryY = 3;
			data.phoneX = 56;
			data.phoneY = -57;

			break;
		}
		case Theme::Theme8:{
			data.primaryColor = lv_color_make(94, 193, 0);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(94, 193, 0);
			data.opacity = LV_OPA_100;
			data.sliderConfig.start = 122;
			data.sliderConfig.end = 6;
			data.sliderConfig.y = 3;
			data.sliderY = 111;
			data.clockY = -23;
			data.batteryX = 87;
			data.batteryY = 5;
			data.phoneX = 56;
			data.phoneY = -57;

			break;
		}
		case Theme::Theme9:{
			data.primaryColor = lv_color_make(255, 255, 0);
			data.textColor = lv_color_make(255, 255, 255);
			data.clockColor = lv_color_make(255, 210, 0);
			data.opacity = LV_OPA_0;
			data.sliderConfig.start = 118;
			data.sliderConfig.end = 8;
			data.sliderConfig.y = 3;
			data.sliderY = 109;
			data.clockY = -18;
			data.batteryX = 96;
			data.batteryY = 4;
			data.phoneX = -46;
			data.phoneY = -56;

			break;
		}
		default:{
			break;
		}
	}

	return data;
}

const static inline ThemeStruct Theme1 = createTheme(Theme::Theme1);
const static inline ThemeStruct Theme2 = createTheme(Theme::Theme2);
const static inline ThemeStruct Theme3 = createTheme(Theme::Theme3);
const static inline ThemeStruct Theme4 = createTheme(Theme::Theme4);
const static inline ThemeStruct Theme5 = createTheme(Theme::Theme5);
const static inline ThemeStruct Theme6 = createTheme(Theme::Theme6);
const static inline ThemeStruct Theme7 = createTheme(Theme::Theme7);
const static inline ThemeStruct Theme8 = createTheme(Theme::Theme8);
const static inline ThemeStruct Theme9 = createTheme(Theme::Theme9);
const static inline ThemeStruct Default = Theme1;

struct SettingsStruct {
	bool notificationSounds = true;
	uint8_t screenBrightness = 100;
	uint8_t sleepTime = 1;
	bool ledEnable = true;
	bool motionDetection = true;
	bool screenRotate = false;
	bool timeFormat24h = true;
	ThemeStruct themeData = Default;
};

class Settings {
public:
	Settings();

	SettingsStruct get();
	void set(SettingsStruct& settings);
	void store();

	static constexpr uint8_t SleepSteps = 5;
	static constexpr const uint32_t SleepSeconds[SleepSteps] = { 0, 30, 60, 2 * 60, 5 * 60 };
	static constexpr const char* SleepText[SleepSteps] = { "OFF", "30 sec", "1 min", "2 min", "5 min" };

private:
	nvs_handle_t handle{};
	SettingsStruct settingsStruct;

	static constexpr const char* NVSNamespace = "Artemis";
	static constexpr const char* BlobName = "Settings";

	void load();
};


#endif //CLOCKSTAR_FIRMWARE_SETTINGS_H
