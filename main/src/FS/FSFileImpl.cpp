#include "FSFileImpl.h"
#include <cstring>
#include <esp_log.h>

static const char* TAG = "FSFile";

FSFileImpl::FSFileImpl(const char* path, const char* mode) : _f(nullptr), _d(nullptr), _path(nullptr), _isDirectory(false), _written(false){
	char* temp = (char*) malloc(strlen(path) + 1);
	if(!temp){
		return;
	}
	sprintf(temp, "%s", path);

	_path = strdup(path);
	if(!_path){
		ESP_LOGE(TAG, "strdup(%s) failed", path);
		free(temp);
		return;
	}

	if(!stat(temp, &_stat)){
		//file found
		if(S_ISREG(_stat.st_mode)){
			_isDirectory = false;
			_f = fopen(temp, mode);
			if(!_f){
				ESP_LOGE(TAG, "fopen(%s) failed", temp);
			}
		}else if(S_ISDIR(_stat.st_mode)){
			_isDirectory = true;
			_d = opendir(temp);
			if(!_d){
				ESP_LOGE(TAG, "opendir(%s) failed", temp);
			}
		}else{
			ESP_LOGE(TAG, "Unknown type 0x%08lX for file %s", ((_stat.st_mode) & _IFMT), temp);
		}
	}else{
		//file not found
		if(!mode || mode[0] == 'r'){
			//try to open as directory
			_d = opendir(temp);
			if(_d){
				_isDirectory = true;
			}else{
				_isDirectory = false;
				//log_w("stat(%s) failed", temp);
			}
		}else{
			//lets create this new file
			_isDirectory = false;
			_f = fopen(temp, mode);
			if(!_f){
				ESP_LOGE(TAG, "fopen(%s) failed", temp);
			}
		}
	}
	free(temp);
}

FSFileImpl::~FSFileImpl(){
	close();
}

void FSFileImpl::close(){
	if(_path){
		free(_path);
		_path = nullptr;
	}
	if(_isDirectory && _d){
		closedir(_d);
		_d = nullptr;
		_isDirectory = false;
	}else if(_f){
		fclose(_f);
		_f = nullptr;
	}
}

FSFileImpl::operator bool(){
	return (_isDirectory && _d != nullptr) || _f != nullptr;
}

time_t FSFileImpl::getLastWrite(){
	_getStat();
	return _stat.st_mtime;
}

void FSFileImpl::_getStat() const{
	if(!_path){
		return;
	}
	char* temp = (char*) malloc(strlen(_path) + 1);
	if(!temp){
		return;
	}
	sprintf(temp, "%s", _path);
	if(!stat(temp, &_stat)){
		_written = false;
	}
	free(temp);
}

size_t FSFileImpl::write(const uint8_t* buf, size_t size){
	if(_isDirectory || !_f || !buf || !size){
		return 0;
	}
	_written = true;
	return fwrite(buf, 1, size, _f);
}

size_t FSFileImpl::read(uint8_t* buf, size_t size){
	if(_isDirectory || !_f || !buf || !size){
		return 0;
	}

	return fread(buf, 1, size, _f);
}

void FSFileImpl::flush(){
	if(_isDirectory || !_f){
		return;
	}
	fflush(_f);
	// workaround for https://github.com/espressif/arduino-esp32/issues/1293
	fsync(fileno(_f));
}

bool FSFileImpl::seek(uint32_t pos, SeekMode mode){
	if(_isDirectory || !_f){
		return false;
	}
	auto rc = fseek(_f, pos, (int) mode);
	return rc == 0;
}

size_t FSFileImpl::position() const{
	if(_isDirectory || !_f){
		return 0;
	}
	return ftell(_f);
}

size_t FSFileImpl::size() const{
	if(_isDirectory || !_f){
		return 0;
	}
	if(_written){
		_getStat();
	}
	return _stat.st_size;
}

const char* FSFileImpl::name() const{
	return (const char*) _path;
}

//to implement
bool FSFileImpl::isDirectory(){
	return _isDirectory;
}

FileImplPtr FSFileImpl::openNextFile(const char* mode){
	if(!_isDirectory || !_d){
		return {};
	}
	struct dirent* file = readdir(_d);
	if(file == nullptr){
		return {};
	}
	if(file->d_type != DT_REG && file->d_type != DT_DIR){
		return openNextFile(mode);
	}
	std::string fname = std::string(file->d_name);
	std::string name = std::string(_path);
	if(!fname.starts_with('/') && !name.ends_with('/')){
		name += '/';
	}
	name += fname;

	return std::make_shared<FSFileImpl>(name.c_str(), mode);
}

void FSFileImpl::rewindDirectory(){
	if(!_isDirectory || !_d){
		return;
	}
	rewinddir(_d);
}

File fs::open(const char* path, const char* mode){
	if(!path || path[0] != '/'){
		ESP_LOGE(TAG, "%s does not start with /", path);
		return FileImplPtr();
	}

	char* temp = (char*) malloc(strlen(path) + 2);
	if(!temp){
		ESP_LOGE(TAG, "malloc failed");
		return FileImplPtr();
	}

	sprintf(temp, "%s", path);

	struct stat st{};
	//file found
	if(!stat(temp, &st)){
		free(temp);
		if(S_ISREG(st.st_mode) || S_ISDIR(st.st_mode)){
			return File(std::make_shared<FSFileImpl>(path, mode));
		}
		ESP_LOGE(TAG, "%s has wrong mode 0x%08lX", path, st.st_mode);
		return FileImplPtr();
	}

	//file not found but mode permits creation
	if(mode && mode[0] != 'r'){
		free(temp);
		return File(std::make_shared<FSFileImpl>(path, mode));
	}

	//try to open this as directory (might be mount point)
	DIR* d = opendir(temp);
	if(d){
		closedir(d);
		free(temp);
		return File(std::make_shared<FSFileImpl>(path, mode));
	}

	ESP_LOGE(TAG, "%s does not exist", temp);
	free(temp);
	return FileImplPtr();
}
