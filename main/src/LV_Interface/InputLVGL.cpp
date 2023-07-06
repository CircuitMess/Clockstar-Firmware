#include "InputLVGL.h"
#include "Pins.hpp"

InputLVGL* InputLVGL::instance = nullptr;
const std::map<Input::Button, lv_key_t> InputLVGL::keyMap = {{ Input::Button::Up,     LV_KEY_LEFT },
															 { Input::Button::Down,   LV_KEY_RIGHT },
															 { Input::Button::Select, LV_KEY_ENTER }};

InputLVGL::InputLVGL() : Threaded("InputLVGL", 1024), queue(QueueSize){
	instance = this;

	Events::listen(Facility::Input, &queue);

	static lv_indev_drv_t inputDriver;
	lv_indev_drv_init(&inputDriver);
	inputDriver.type = LV_INDEV_TYPE_ENCODER;
	inputDriver.long_press_repeat_time = 20;
	inputDriver.long_press_time = 350;
	inputDriver.read_cb = [](lv_indev_drv_t* drv, lv_indev_data_t* data){ InputLVGL::getInstance()->read(drv, data); };
	inputDevice = lv_indev_drv_register(&inputDriver);

	start();
}

void InputLVGL::read(lv_indev_drv_t* drv, lv_indev_data_t* data){
	if(keyMap.count(lastKey) == 0) return;
	data->key = keyMap.at(lastKey);
	data->state = (action == Input::Data::Action::Press) ? LV_INDEV_STATE_PRESSED : LV_INDEV_STATE_RELEASED;
}

InputLVGL* InputLVGL::getInstance(){
	return instance;
}

void InputLVGL::loop(){
	Event event{};

	if(queue.get(event, portMAX_DELAY)){
		auto inputData = *((Input::Data*) event.data);
		lastKey = inputData.btn;
		action = inputData.action;
	}
}

lv_indev_t* InputLVGL::getIndev() const{
	return inputDevice;
}
