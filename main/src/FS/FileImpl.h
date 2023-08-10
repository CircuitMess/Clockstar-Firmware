#ifndef BIT_FIRMWARE_FILEIMPL_H
#define BIT_FIRMWARE_FILEIMPL_H

#include <string>
#include <memory>

class FileImpl;

typedef std::shared_ptr<FileImpl> FileImplPtr;

enum class SeekMode : uint8_t {
	SeekSet = SEEK_SET,
	SeekCur = SEEK_CUR,
	SeekEnd = SEEK_END
};

class FileImpl {
public:
	virtual ~FileImpl() = default;
	virtual size_t write(const uint8_t* buf, size_t size) = 0;
	virtual size_t read(uint8_t* buf, size_t size) = 0;
	virtual void flush() = 0;
	virtual bool seek(uint32_t pos, SeekMode mode) = 0;
	virtual size_t position() const = 0;
	virtual size_t size() const = 0;
	virtual void close() = 0;
	virtual time_t getLastWrite() = 0;
	virtual const char* name() const = 0;
	virtual bool isDirectory() = 0;
	virtual FileImplPtr openNextFile(const char* mode) = 0;
	virtual void rewindDirectory() = 0;
	virtual operator bool() = 0;
};


#endif //BIT_FIRMWARE_FILEIMPL_H
