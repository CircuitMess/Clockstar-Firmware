#ifndef BIT_FIRMWARE_FSFILEIMPL_H
#define BIT_FIRMWARE_FSFILEIMPL_H

#include <sys/dirent.h>
#include <sys/stat.h>
#include "FileImpl.h"
#include "File.h"

class FSFileImpl : public FileImpl {
public:
	FSFileImpl(const char* path, const char* mode);
	~FSFileImpl() override;
	size_t write(const uint8_t* buf, size_t size) override;
	size_t read(uint8_t* buf, size_t size) override;
	void flush() override;
	bool seek(uint32_t pos, SeekMode mode) override;
	size_t position() const override;
	size_t size() const override;
	void close() final;
	const char* name() const override;
	time_t getLastWrite() override;
	bool isDirectory() override;
	FileImplPtr openNextFile(const char* mode) override;
	void rewindDirectory() override;
	operator bool() override;


protected:
	FILE* _f;
	DIR* _d;
	char* _path;
	bool _isDirectory;
	mutable struct stat _stat;
	mutable bool _written;

	void _getStat() const;

};

namespace fs {

extern File open(const char* path, const char* mode = "r");

}


#endif //BIT_FIRMWARE_FSFILEIMPL_H
