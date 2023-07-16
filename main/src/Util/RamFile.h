#ifndef CLOCKSTAR_FIRMWARE_RAMFILE_H
#define CLOCKSTAR_FIRMWARE_RAMFILE_H

#include <cstdint>
#include <vector>
#include <cstddef>
#include <string>

class RamFile {
public:
	RamFile(const char* path, bool use32bAligned);
	virtual ~RamFile();

	size_t read(void* dest, size_t len);
	void seek(size_t pos, int whence = SEEK_SET);
	size_t pos();

	size_t size();
	std::string path();

private:
	uint8_t* data = nullptr;
	size_t cursor = 0;
	std::string filePath;
	size_t fileSize = 0;

};


#endif //CLOCKSTAR_FIRMWARE_RAMFILE_H
