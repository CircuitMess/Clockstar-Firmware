#include "File.h"

File::File(FileImplPtr p) : _p(std::move(p)){

}

size_t File::write(uint8_t c){
	if(!_p){
		return 0;
	}

	return _p->write(&c, 1);
}

time_t File::getLastWrite(){
	if(!_p){
		return 0;
	}

	return _p->getLastWrite();
}

size_t File::write(const uint8_t* buf, size_t size){
	if(!_p){
		return 0;
	}

	return _p->write(buf, size);
}

int File::available(){
	if(!_p){
		return false;
	}

	return _p->size() - _p->position();
}

int File::read(){
	if(!_p){
		return -1;
	}

	uint8_t result;
	if(_p->read(&result, 1) != 1){
		return -1;
	}

	return result;
}

size_t File::read(uint8_t* buf, size_t size){
	if(!_p){
		return -1;
	}

	return _p->read(buf, size);
}

int File::peek(){
	if(!_p){
		return -1;
	}

	size_t curPos = _p->position();
	int result = read();
	seek(curPos, SeekMode::SeekSet);
	return result;
}

void File::flush(){
	if(!_p){
		return;
	}

	_p->flush();
}

bool File::seek(uint32_t pos, SeekMode mode){
	if(!_p){
		return false;
	}

	return _p->seek(pos, mode);
}

size_t File::position() const{
	if(!_p){
		return 0;
	}

	return _p->position();
}

size_t File::size() const{
	if(!_p){
		return 0;
	}

	return _p->size();
}

void File::close(){
	if(_p){
		_p->close();
		_p = nullptr;
	}
}

File::operator bool() const{
	return *_p;
}

const char* File::name() const{
	if(!_p){
		return nullptr;
	}

	return _p->name();
}

bool File::isDirectory(){
	if(!_p){
		return false;
	}
	return _p->isDirectory();
}

File File::openNextFile(const char* mode){
	if(!_p){
		return {};
	}
	return _p->openNextFile(mode);
}

void File::rewindDirectory(){
	if(!_p){
		return;
	}
	_p->rewindDirectory();
}
