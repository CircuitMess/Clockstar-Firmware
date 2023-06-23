#include "Scr.h"
#include "Devices/IMU.h"
#include <sstream>

Scr::Scr(IMU& imu) : imu(imu), evtQueue(24), evtChecker([this](){ for(;;){ check(); } }, "Scr-Evt"), gyroUpdater([this](){ for(;;){ gyroUpdate(); } }, "Scr-Gyro"), textQueue(12){
	lv_obj_set_size(obj, 128, 128);
	lv_obj_set_flex_flow(obj, LV_FLEX_FLOW_COLUMN);
	lv_obj_set_flex_align(obj, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START, LV_FLEX_ALIGN_START);
	lv_obj_set_style_bg_color(obj, lv_color_black(), 0);
	lv_obj_set_style_bg_opa(obj, LV_OPA_COVER, 0);

	lv_style_init(&textStyle);
	lv_style_set_text_color(&textStyle, lv_color_white());
	lv_style_set_text_font(&textStyle, &lv_font_unscii_8);
	lv_style_set_width(&textStyle, LV_PCT(100));

	for(auto text : { &gyroX, &gyroY, &gyroZ, &singleTap, &sigMotion, &wristTilt }){
		*text = lv_label_create(obj);
		lv_obj_add_style(*text, &textStyle, 0);
		lv_label_set_text(*text, "");
		lv_label_set_long_mode(*text, LV_LABEL_LONG_SCROLL_CIRCULAR);
	}

	Events::listen(Facility::Motion, &evtQueue);
	evtChecker.start();

	imu.enableGyroAccelero(true);
	imu.enableMotionDetection(true);
	imu.setWristPosition(IMU::WatchPosition::FaceUp);
	imu.setTiltDirection(IMU::TiltDirection::Lifted);
	gyroUpdater.start();
}

Scr::~Scr(){

}

void Scr::loop(){
	std::unique_ptr<TextRequest> request;
	while((request = textQueue.get(0))){
		lv_label_set_text(request->label, request->text.c_str());
	}
}

void Scr::requestText(lv_obj_t* label, std::string text, uint32_t count){
	std::stringstream str;
	str << text << ": " << count;
	textQueue.post(std::make_unique<TextRequest>(label, str.str()));
}

void Scr::requestText(lv_obj_t* label, std::string text){
	textQueue.post(std::make_unique<TextRequest>(label, text));
}

void Scr::check(){
	Event evt;
	if(evtQueue.get(evt, portMAX_DELAY) == false) return;
	if(evt.facility != Facility::Motion){
		free(evt.data);
		return;
	}

	printf("Evt: ");

	std::unique_ptr<IMU::Event> data((IMU::Event*) evt.data);
	if(data->action == IMU::Event::SingleTap){
		printf("single tap\n");
		counts.singleTap++;
		requestText(singleTap, "Single tap", counts.singleTap);
	}else if(data->action == IMU::Event::SignMotion){
		printf("sig motion\n");
		counts.sigMotion++;
		requestText(sigMotion, "Sig motion", counts.sigMotion);
	}else if(data->action == IMU::Event::WristTilt){
		printf("wrist tilt\n");
		counts.wristTilt++;
		requestText(wristTilt, "Wrist tilt", counts.wristTilt);
	}else if(data->action == IMU::Event::FIFO){
		printf("FIFO\n");
	}else{
		printf("unknown\n");
	}
}

void Scr::gyroUpdate(){
	IMU::Sample sample;
	if(imu.getNextSample(sample, portMAX_DELAY) == false) return;

	requestText(gyroX, "Gyro X", sample.gyroX);
	requestText(gyroY, "Gyro Y", sample.gyroY);
	requestText(gyroZ, "Gyro Z", sample.gyroZ);
}
