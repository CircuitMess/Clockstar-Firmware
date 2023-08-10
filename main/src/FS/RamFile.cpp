#include "RamFile.h"
#include <cstring>
#include <esp_log.h>
#include <esp_heap_caps.h>

static const char* TAG = "RamFile";

RamFile::RamFile(File file, bool use32bAligned) : filePath(file.name()){
	if(!file){
		ESP_LOGE(TAG, "Couldn't open file: %s", file.name());
		return;
	}

	file.seek(0);
	fileSize = file.size();

	if(fileSize == 0){
		ESP_LOGE(TAG, "File is empty: %s", file.name());
		file.close();
		return;
	}
	size_t allocSize = fileSize;
	if(use32bAligned){
		auto rest = fileSize % 4;
		if(rest != 0){
			allocSize += (4 - rest);
		}
	}

	data = (uint8_t*) heap_caps_malloc(allocSize, MALLOC_CAP_INTERNAL | (use32bAligned ? MALLOC_CAP_32BIT : MALLOC_CAP_8BIT));
	if(data == nullptr){
		fileSize = 0;
		ESP_LOGE(TAG, "Couldn't allocate memory for %s. Need %zu B, largest block: %zu B", file.name(), allocSize,
				 heap_caps_get_largest_free_block(MALLOC_CAP_INTERNAL | (use32bAligned ? MALLOC_CAP_32BIT : MALLOC_CAP_8BIT)));
		file.close();

		return;
	}

	file.read(data, fileSize);
	file.close();
}

RamFile::~RamFile(){
	free(data);
}

size_t RamFile::write(const uint8_t* buf, size_t size){
	//TODO - implement writing
	return 0;
}

size_t IRAM_ATTR RamFile::read(uint8_t* dest, size_t len){
	if(cursor >= fileSize) return 0;
	len = std::min(len, fileSize - cursor);
	if(len <= 0) return 0;

	memcpy(dest, data + cursor, len);
	cursor += len;

	return len;
}

void RamFile::flush(){

}

bool RamFile::seek(uint32_t pos, SeekMode whence){
	if(whence == SeekMode::SeekSet){
		cursor = pos;
	}else if(whence == SeekMode::SeekCur){
		cursor += pos;
	}else if(whence == SeekMode::SeekEnd){
		cursor = fileSize - pos;
	}
	return true;
}

size_t RamFile::position() const{
	return cursor;
}

size_t RamFile::size() const{
	return fileSize;
}

const char* RamFile::name() const{
	return filePath.c_str();
}

void RamFile::close(){
	delete data;

	data = nullptr;
	fileSize = 0;
	filePath = "";
}

time_t RamFile::getLastWrite(){
	return 0;
}

bool RamFile::isDirectory(){
	return false;
}

FileImplPtr RamFile::openNextFile(const char* mode){
	return FileImplPtr();
}

void RamFile::rewindDirectory(){

}

RamFile::operator bool(){
	return data != nullptr;
}

File RamFile::open(const File& file, bool use32bAligned){
	auto f = std::make_shared<RamFile>(file, use32bAligned);
	return File(f);
}

