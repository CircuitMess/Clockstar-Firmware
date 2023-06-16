#include "Client.h"
#include <mjson.h>
#include <esp_log.h>

static const char* TAG = "Bangle";

Bangle::Client::Client(BLE::Server* server) : Threaded("Bangle", 4 * 1024), uart(server){
	start();
}

Bangle::Client::~Client(){
	stop();
}

void Bangle::Client::actionPos(uint32_t uid){

}

void Bangle::Client::actionNeg(uint32_t uid){

}

void Bangle::Client::loop(){
	auto line = uart.scan_nl(portMAX_DELAY);
	if(line.empty()) return;

	int comlen;
	const char* com;
	if(mjson_find((char*) line.data(), line.size(), "$.t", &com, &comlen) != MJSON_TOK_STRING){
		ESP_LOGW(TAG, "Invalid JSON, missing command: %s", line.data());
		return;
	}

	std::string t(com + 1, com + comlen - 1);

	auto comp = [](const char* a, const char* b){
		return strcmp(a, b);
	};

	static const std::unordered_map<std::string, std::function<void(const std::vector<uint8_t>& line)>> handlers = {
			{ "is_gps_active", [this](const std::vector<uint8_t>& line){ handle_isGpsActive(); } }
	};

	auto handler = handlers.find(t);
	if(handler == handlers.end()){
		ESP_LOGW(TAG, "Unhandled command from phone: %s", t.data());
		return;
	}

	handler->second(line);
}

void Bangle::Client::handle_isGpsActive(){
	uart.printf("{ t: \"gps_power\", status: false }");
}
