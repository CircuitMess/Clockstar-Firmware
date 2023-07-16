#ifndef CLOCKSTAR_FIRMWARE_SETTINGS_H
#define CLOCKSTAR_FIRMWARE_SETTINGS_H

#include <nvs.h>

struct SettingsStruct {
	bool notificationSounds = true;
	uint8_t screenBrightness = 200;
};

class Settings {
public:
	Settings();

	SettingsStruct get();
	void set(SettingsStruct& settings);

private:
	nvs_handle_t handle{};
	SettingsStruct settingsStruct;

	static constexpr const char* NVSNamespace = "Clockstar";
	static constexpr const char* BlobName = "Settings";

	void store();
	void load();
};


#endif //CLOCKSTAR_FIRMWARE_SETTINGS_H
