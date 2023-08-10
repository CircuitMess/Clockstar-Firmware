#ifndef BIT_FIRMWARE_RAMFILE_H
#define BIT_FIRMWARE_RAMFILE_H

#include <cstdint>
#include <vector>
#include <cstddef>
#include <string>
#include "FileImpl.h"
#include "File.h"

class RamFile : public FileImpl {
public:
	RamFile(File file, bool use32bAligned = false);
	~RamFile() override;

	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* dest, size_t len) override;
	void flush() override;
	bool seek(uint32_t pos, SeekMode whence) override;
	size_t position() const override;
	size_t size() const override;
	void close() override;
	time_t getLastWrite() override;
	const char* name() const override;
	bool isDirectory() override;
	FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory() override;
	operator bool() override;

	static File open(const File& file, bool use32bAligned = false);

private:
	uint8_t* data = nullptr;
	size_t cursor = 0;
	std::string filePath;
	size_t fileSize = 0;

};


#endif //BIT_FIRMWARE_RAMFILE_H
