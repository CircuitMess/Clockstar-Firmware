#ifndef BIT_FIRMWARE_SPIFFS_H
#define BIT_FIRMWARE_SPIFFS_H

#include "File.h"

class SPIFFS {
public:
	static File open(const char* path, const char* mode = "r");
private:
	static constexpr const char* prefix = "/spiffs";
};


#endif //BIT_FIRMWARE_SPIFFS_H
