#ifndef BIT_FIRMWARE_FILE_H
#define BIT_FIRMWARE_FILE_H

#include "FileImpl.h"
#include <fstream>
#include <utility>

class File {
public:
	File(FileImplPtr p = FileImplPtr());

	size_t write(uint8_t);
	size_t write(const uint8_t* buf, size_t size);
	int available();
	int read();
	int peek();
	void flush();
	size_t read(uint8_t* buf, size_t size);

	size_t readBytes(char* buffer, size_t length){
		return read((uint8_t*) buffer, length);
	}

	bool seek(uint32_t pos, SeekMode mode);

	bool seek(uint32_t pos){
		return seek(pos, SeekMode::SeekSet);
	}

	size_t position() const;
	size_t size() const;
	void close();
	operator bool() const;
	time_t getLastWrite();
	const char* name() const;

	bool isDirectory(void);
	File openNextFile(const char* mode = "r");
	void rewindDirectory(void);

protected:
	FileImplPtr _p;


};


#endif //BIT_FIRMWARE_FILE_H
