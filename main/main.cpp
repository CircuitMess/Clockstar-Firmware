#include "Devices/Display.h"
#include <esp_spiffs.h>
#include "Util/stdafx.h"
#include "FS/SPIFFS.h"
#include "GIF/GIFSprite.h"
#include <esp_log.h>
#include "Util/Threaded.h"
#include "Pins.hpp"
#include <termios.h>

bool initSPIFFS(){
	esp_vfs_spiffs_conf_t conf = {
			.base_path = "/spiffs",
			.partition_label = "storage",
			.max_files = 8,
			.format_if_mount_failed = false
	};

	auto ret = esp_vfs_spiffs_register(&conf);
	if(ret != ESP_OK){
		if(ret == ESP_FAIL){
			ESP_LOGE("FS", "Failed to mount or format filesystem");
		}else if(ret == ESP_ERR_NOT_FOUND){
			ESP_LOGE("FS", "Failed to find SPIFFS partition");
		}else{
			ESP_LOGE("FS", "Failed to initialize SPIFFS (%s)", esp_err_to_name(ret));
		}
		return false;
	}

	return true;
}

Display* disp;

class GifScreen {
public:
	GifScreen(){
		FILE* f = fopen("/spiffs/gif.gif", "r");
		if(f == nullptr){
			printf("No gif\n");
			return;
		}
		fclose(f);

		File file = SPIFFS::open("/gif.gif");
		gif = new GIFSprite(file);
		gif->setLoopMode(GIF::Infinite);
		frameTime = millis();
	}

	virtual ~GifScreen(){
		delete gif;
	}

	void loop(){
		uint32_t now = millis();
		auto diff = now - frameTime;
		frameTime = now;

		gif->loop(diff*1000);
		auto sprite = gif->getSprite();
		disp->getLGFX().pushImage(0, 0, sprite.width(), sprite.height(), sprite.getBuffer(), 0x002400);
	}

private:
	GIFSprite* gif = nullptr;

	uint32_t frameTime;
};

GifScreen* scr;

int bread(void* buff, size_t size, uint32_t timeout = 0){
	uint8_t* buf = (uint8_t*) buff;

	uint32_t bytesRead = 0;
	uint32_t startTime = millis();
	while(bytesRead < size){
		if(timeout != 0 && millis() - startTime >= timeout) return bytesRead;

		size_t now = std::min(256UL, size - bytesRead);
		int run = read(0, buf + bytesRead, now);
		if(run <= 0){
			vTaskDelay(1);
			continue;
		}
		bytesRead += run;
	}
	return bytesRead;
}

void ok(){
	printf("OK");
	fflush(stdout);
}

void checkUpload(){
	uint32_t size;
	if(bread(&size, 4, 50) != 4) return;

	uint32_t checksum;
	bread(&checksum, 4);

	delete scr;
	scr = nullptr;

	unlink("/spiffs/gif.gif");
	FILE* f = fopen("/spiffs/gif.gif", "wb");

	ok();

	uint32_t sum = 0;
	uint32_t bytesRead = 0;
	uint8_t buf[256];
	while(bytesRead < size){
		size_t readNow = std::min(256UL, size - bytesRead);
		bread(buf, readNow);

		fwrite(buf, 1, readNow, f);
		fflush(f);

		for(int i = 0; i < readNow; i++){
			sum += buf[i];
		}
		bytesRead += readNow;

		ok();

		vTaskDelay(10);
	}
	fflush(f);
	fclose(f);

	if(sum != checksum){
		printf("1");
		fflush(stdout);
		return;
	}
	printf("0");
	fflush(stdout);

	vTaskDelay(1000);
	esp_restart();
}

void init(){
	if(!initSPIFFS()) return;
	freopen(nullptr, "rb", stdin);

	gpio_set_direction((gpio_num_t) PIN_BL, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t) PIN_BL, 0);

	disp = new Display();

	scr = new GifScreen();
	auto ui = new ThreadedClosure([](){
		if(scr){
			scr->loop();
		}
		checkUpload();
		vTaskDelay(5);
	}, "UI", 12*1024);
	ui->start();
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}
