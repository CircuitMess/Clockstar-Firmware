#ifndef CLOCKSTAR_FIRMWARE_SETTINGS_H
#define CLOCKSTAR_FIRMWARE_SETTINGS_H

#include <nvs.h>
#include "core/lv_theme.h"

enum class Theme : uint8_t {
	Default [[maybe_unused]],
	Theme1 [[maybe_unused]],
	Theme2 [[maybe_unused]],
	Theme3 [[maybe_unused]],
	Theme4 [[maybe_unused]],
	Theme5 [[maybe_unused]],
	Theme6 [[maybe_unused]],
	Theme7 [[maybe_unused]],
	Theme8 [[maybe_unused]],
	Theme9 [[maybe_unused]]
};

struct ThemeStruct {
	Theme theme = Theme::Default;
	lv_theme_t* visualTheme = nullptr;
};

const static inline ThemeStruct DefaultTheme = {};
const static inline ThemeStruct Theme1 = { Theme::Theme1 };
const static inline ThemeStruct Theme2 = { Theme::Theme2 };
const static inline ThemeStruct Theme3 = { Theme::Theme3 };
const static inline ThemeStruct Theme4 = { Theme::Theme4 };
const static inline ThemeStruct Theme5 = { Theme::Theme5 };
const static inline ThemeStruct Theme6 = { Theme::Theme6 };
const static inline ThemeStruct Theme7 = { Theme::Theme7 };
const static inline ThemeStruct Theme8 = { Theme::Theme8 };
const static inline ThemeStruct Theme9 = { Theme::Theme9 };

struct SettingsStruct {
	bool notificationSounds = true;
	uint8_t screenBrightness = 100;
	uint8_t sleepTime = 1;
	bool ledEnable = true;
	bool motionDetection = true;
	bool screenRotate = false;
	bool timeFormat24h = true;
	ThemeStruct theme = {};
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
