#include "SPIFFS.h"
#include "FSFileImpl.h"

File SPIFFS::open(const char* path, const char* mode){
	std::string p = std::string(SPIFFS::prefix) + std::string(path);
	return fs::open(p.c_str(), mode);
}
