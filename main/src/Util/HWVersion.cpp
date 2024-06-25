#include "HWVersion.h"

bool HWVersion::check(){
	uint16_t version = 0;

	const esp_err_t err = esp_efuse_read_field_blob((const esp_efuse_desc_t**) Efuse_ver, &version, 16);
	if(err != ESP_OK){
		return false;
	}

	if(version == Version){
		return true;
	}

	ESP_LOGE("Hardware check", "Hardware version (0x%04x) does not match software version (0x%04x).", version, Version);

	return false;
}

bool HWVersion::write(){
	esp_err_t err = esp_efuse_batch_write_begin();
	if(err != ESP_OK){
		return false;
	}

	err = esp_efuse_write_field_blob((const esp_efuse_desc_t**) Efuse_ver, &Version, 16);
	if(err != ESP_OK){
		return false;
	}

	err = esp_efuse_batch_write_commit();
	if(err != ESP_OK){
		return false;
	}

	return true;
}
