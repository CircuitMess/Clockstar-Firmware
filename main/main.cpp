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

class Serial : public Threaded {
public:
	Serial() : Threaded("Serial", 6 * 1024){
		queue = xQueueCreate(2048, 1);
		start();
	}

	size_t available(){
		return uxQueueMessagesWaiting(queue);
	}

	void read(uint8_t* buf, size_t len){
		size_t copied = 0;
		while(copied < len){
			if(!xQueueReceive(queue, buf + copied, portMAX_DELAY)) continue;
			copied++;
		}
	}

	void read(void* buf, size_t len){
		read((uint8_t*) buf, len);
	}

private:
	QueueHandle_t queue;

	void loop() override{
		uint8_t buf[256];
		int bytes;
		while((bytes = ::read(0, buf, 256)) > 0){
			for(int i = 0; i < bytes; i++){
				xQueueSend(queue, &buf[i], portMAX_DELAY);
			}
		}
		vTaskDelay(1);
	}

};

Serial* serial;

void ok(){
	printf("OK");
	fflush(stdout);
}

void checkUpload(){
	if(serial->available() < 4) return;

	uint32_t size;
	serial->read(&size, 4);

	uint32_t checksum;
	serial->read(&checksum, 4);

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
		serial->read(buf, readNow);

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

	for(;;){
		printf("Received all %lu bytes. Our sum: %lu, received sum: %lu\n", size, sum, checksum);
		vTaskDelay(1000);
	}

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
	//fflush(0);
	//freopen(nullptr, "rb", stdin);

	gpio_set_direction((gpio_num_t) PIN_BL, GPIO_MODE_OUTPUT);
	gpio_set_level((gpio_num_t) PIN_BL, 0);

	disp = new Display();

	//serial = new Serial();

	scr = new GifScreen();
	auto ui = new ThreadedClosure([](){
		if(scr){
			scr->loop();
		}
		//checkUpload();
		vTaskDelay(5);
	}, "UI", 12*1024);
	ui->start();
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}
