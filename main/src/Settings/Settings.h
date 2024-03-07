#ifndef CLOCKSTAR_FIRMWARE_SETTINGS_H
#define CLOCKSTAR_FIRMWARE_SETTINGS_H

#include <nvs.h>
#include "core/lv_theme.h"

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
	lv_color_t primaryColor;
	uint8_t opacity;
	lv_color_t textColor;
	lv_color_t clockColor;
};

inline static ThemeStruct createTheme(Theme theme){
	ThemeStruct data = {.theme = theme};

	switch(theme){
		case Theme::Theme1:{
			data.primaryColor = lv_color_make(255, 101, 0);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(255, 101, 0);
			data.opacity = LV_OPA_100;
			break;
		}
		case Theme::Theme2:{
			data.primaryColor = lv_color_make(255, 38, 116);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(255, 38, 116);
			data.opacity = LV_OPA_100;
			break;
		}
		case Theme::Theme3:{
			data.primaryColor = lv_color_make(255, 255, 255);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(255, 255, 255);
			data.opacity = LV_OPA_100;
			break;
		}
		case Theme::Theme4:{
			data.primaryColor = lv_color_make(38, 43, 68);
			data.textColor = lv_color_make(192, 203, 220);
			data.clockColor = lv_color_make(38, 43, 68);
			data.opacity = LV_OPA_100;
			break;
		}
		case Theme::Theme5:{
			data.primaryColor = lv_color_make(244, 180, 27);
			data.textColor = lv_color_make(244, 180, 27);
			data.clockColor = lv_color_make(244, 180, 27);
			data.opacity = LV_OPA_0;
			break;
		}
		case Theme::Theme6:{
			data.primaryColor = lv_color_make(0, 0, 255);
			data.textColor = lv_color_make(255, 255, 0);
			data.clockColor = lv_color_make(255, 255, 255);
			data.opacity = LV_OPA_100;
			break;
		}
		case Theme::Theme7:{
			data.primaryColor = lv_color_make(251, 247, 54);
			data.textColor = lv_color_make(251, 242, 54);
			data.clockColor = lv_color_make(251, 247, 54);
			data.opacity = LV_OPA_0;
			break;
		}
		case Theme::Theme8:{
			data.primaryColor = lv_color_make(94, 193, 0);
			data.textColor = lv_color_make(0, 0, 0);
			data.clockColor = lv_color_make(94, 193, 0);
			data.opacity = LV_OPA_100;
			break;
		}
		case Theme::Theme9:{
			data.primaryColor = lv_color_make(255, 255, 0);
			data.textColor = lv_color_make(255, 255, 255);
			data.clockColor = lv_color_make(255, 210, 0);
			data.opacity = LV_OPA_0;
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

	static constexpr const char* NVSNamespace = "Clockstar";
	static constexpr const char* BlobName = "Settings";

	void load();
};


#endif //CLOCKSTAR_FIRMWARE_SETTINGS_H
