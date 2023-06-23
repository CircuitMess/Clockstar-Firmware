#include "IMU.h"
#include <Util/Events.h>
#include <driver/gpio.h>
#include <esp_log.h>
#include "Pins.hpp"

static const char* TAG = "IMU";

IMU::IMU(I2C& i2c) : i2c(i2c), fifoSamples(MaxReads), thread1([this](){ thread1Func(); }, "IMU1"), thread2([this](){ thread2Func(); }, "IMU2"){
	sem1 = xSemaphoreCreateBinary();
	sem2 = xSemaphoreCreateBinary();

	thread1.start();
	thread2.start();
}

IMU::~IMU(){
	vSemaphoreDelete(sem1);
	vSemaphoreDelete(sem2);

	thread1.stop();
	thread2.stop();
}

bool IMU::init(){
	// TODO: make sure chip registers and interrupts are reset before proceesing.
	//  The software reset here doesn't seem to cut it: INT2 is staying high if
	//  it was high before the reset
	lsm6ds3tr_c_reset_set(&ctx, 1);
	vTaskDelay(50);

	uint8_t id;
	lsm6ds3tr_c_device_id_get(&ctx, &id);
	if(id != LSM6DS3TR_C_ID){
		ESP_LOGE(TAG, "Init error, got ID 0x%x, expected 0x%x", id, LSM6DS3TR_C_ID);
		return false;
	}

	lsm6ds3tr_c_block_data_update_set(&ctx, 1); //for reading 2 byte long values

	//accelero setup
	lsm6ds3tr_c_xl_filter_analog_set(&ctx, LSM6DS3TR_C_XL_ANA_BW_400Hz);
	lsm6ds3tr_c_xl_full_scale_set(&ctx, LSM6DS3TR_C_16g);
	lsm6ds3tr_c_xl_data_rate_set(&ctx, LSM6DS3TR_C_XL_ODR_104Hz);

	//gyro setup
	lsm6ds3tr_c_gy_data_rate_set(&ctx, LSM6DS3TR_C_GY_ODR_104Hz);
	lsm6ds3tr_c_gy_full_scale_set(&ctx, LSM6DS3TR_C_2000dps);
	lsm6ds3tr_c_gy_band_pass_set(&ctx, LSM6DS3TR_C_HP_65mHz_LP1_NORMAL);

	//FIFO setup
	lsm6ds3tr_c_fifo_watermark_set(&ctx, ReadingsWatermark);
	lsm6ds3tr_c_fifo_xl_batch_set(&ctx, LSM6DS3TR_C_FIFO_XL_NO_DEC);
	lsm6ds3tr_c_fifo_gy_batch_set(&ctx, LSM6DS3TR_C_FIFO_GY_NO_DEC);
	lsm6ds3tr_c_fifo_data_rate_set(&ctx, LSM6DS3TR_C_FIFO_104Hz);
	enableGyroAccelero(false);

	//wrist tilt interrupt setup
	lsm6ds3tr_c_wrist_tilt_sens_set(&ctx, 1);
	uint8_t tiltLatency = 1; // total latency is tiltLatency * 40ms
	lsm6ds3tr_c_tilt_latency_set(&ctx, &tiltLatency);
	uint8_t tiltThresh = 32; // total thresh is tiltThresh * 15.625mg
	lsm6ds3tr_c_tilt_threshold_set(&ctx, &tiltThresh);
	lsm6ds3tr_c_a_wrist_tilt_mask_t tiltMask = { 0, 0, 0, 0, 0, 0, 0 };
	lsm6ds3tr_c_tilt_src_set(&ctx, &tiltMask);

	//significant motion setup
	lsm6ds3tr_c_motion_sens_set(&ctx, 0);
	uint8_t motionSenseThresh = SignificantMotionSens;
	lsm6ds3tr_c_motion_threshold_set(&ctx, &motionSenseThresh);

	//tap setup
	lsm6ds3tr_c_tap_detection_on_x_set(&ctx, 0);
	lsm6ds3tr_c_tap_detection_on_y_set(&ctx, 0);
	lsm6ds3tr_c_tap_detection_on_z_set(&ctx, 1);
	lsm6ds3tr_c_tap_threshold_x_set(&ctx, 0x01);
	lsm6ds3tr_c_tap_dur_set(&ctx, 0);
	lsm6ds3tr_c_tap_quiet_set(&ctx, 3);
	lsm6ds3tr_c_tap_shock_set(&ctx, 3);
	lsm6ds3tr_c_tap_mode_set(&ctx, LSM6DS3TR_C_BOTH_SINGLE_DOUBLE);
	lsm6ds3tr_c_int_notification_set(&ctx, LSM6DS3TR_C_INT_LATCHED);


	lsm6ds3tr_c_pin_int1_route_set(&ctx, { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 });
	lsm6ds3tr_c_pin_int2_route_set(&ctx, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }); //wrist tilt to INT2

	gpio_install_isr_service(ESP_INTR_FLAG_LOWMED | ESP_INTR_FLAG_SHARED);

	gpio_config_t io_conf = {};
	io_conf.intr_type = GPIO_INTR_POSEDGE;
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
	io_conf.pull_down_en = GPIO_PULLDOWN_DISABLE;

	io_conf.pin_bit_mask = (1ULL << IMU_INT1);
	gpio_config(&io_conf);
	gpio_isr_handler_add((gpio_num_t) IMU_INT1, isr1, this);

	io_conf.pin_bit_mask = (1ULL << IMU_INT2);
	gpio_config(&io_conf);
	gpio_isr_handler_add((gpio_num_t) IMU_INT2, isr2, this);

	return true;
}

int32_t IMU::platform_write(void* hndl, uint8_t reg, const uint8_t* data, uint16_t len){
	auto imu = (IMU*) hndl;
	return imu->i2c.writeReg(Addr, reg, data, len, 10);
}

int32_t IMU::platform_read(void* hndl, uint8_t reg, uint8_t* data, uint16_t len){
	auto imu = (IMU*) hndl;
	return imu->i2c.readReg(Addr, reg, data, len, 10);
}

bool IMU::getNextSample(IMU::Sample& sample, TickType_t wait){
	return fifoSamples.get(sample, wait);
}

void IMU::clearFifo(){
	//setting to bypass mode resets the fifo buffer
	lsm6ds3tr_c_fifo_mode_set(&ctx, LSM6DS3TR_C_BYPASS_MODE);
	vTaskDelay(5);
	lsm6ds3tr_c_fifo_mode_set(&ctx, LSM6DS3TR_C_STREAM_MODE);
}

void IMU::printInterruptInfo(){
	lsm6ds3tr_c_all_sources_t src;
	lsm6ds3tr_c_all_sources_get(&ctx, &src);
/*	printf("wrist tilt mask:\n");
	printf("zneg: %d\n", src.a_wrist_tilt_mask.wrist_tilt_mask_zneg);
	printf("zpos: %d\n", src.a_wrist_tilt_mask.wrist_tilt_mask_zpos);
	printf("yneg: %d\n", src.a_wrist_tilt_mask.wrist_tilt_mask_yneg);
	printf("ypos: %d\n", src.a_wrist_tilt_mask.wrist_tilt_mask_ypos);
	printf("xneg: %d\n", src.a_wrist_tilt_mask.wrist_tilt_mask_xneg);
	printf("xpos: %d\n", src.a_wrist_tilt_mask.wrist_tilt_mask_xpos);*/

	printf("wrist tilt interrupt source:\n");
	printf("zneg: %d\n", src.wrist_tilt_ia.wrist_tilt_ia_zneg);
	printf("zpos: %d\n", src.wrist_tilt_ia.wrist_tilt_ia_zpos);
	printf("yneg: %d\n", src.wrist_tilt_ia.wrist_tilt_ia_yneg);
	printf("ypos: %d\n", src.wrist_tilt_ia.wrist_tilt_ia_ypos);
	printf("xneg: %d\n", src.wrist_tilt_ia.wrist_tilt_ia_xneg);
	printf("xpos: %d\n", src.wrist_tilt_ia.wrist_tilt_ia_xpos);

	printf("TILT_IA flag: %d\n", src.func_src1.tilt_ia);
	printf("WRIST_TILT_IA flag: %d\n", src.func_src2.wrist_tilt_ia);
	printf("SIGN_MOTION: %d\n", src.func_src1.sign_motion_ia);
	printf("SINGLE TAP: %d\n", src.tap_src.single_tap);
	printf("DOUBLE_TAP: %d\n", src.tap_src.double_tap);
	printf("x_tap: %d\n", src.tap_src.x_tap);
	printf("y_tap: %d\n", src.tap_src.y_tap);
	printf("z_tap: %d\n", src.tap_src.z_tap);

}

void IRAM_ATTR IMU::isr1(void* arg){
	auto imu = static_cast<IMU*>(arg);
	xSemaphoreGiveFromISR(imu->sem1, nullptr);
}

void IRAM_ATTR IMU::isr2(void* arg){
	auto imu = static_cast<IMU*>(arg);
	xSemaphoreGiveFromISR(imu->sem2, nullptr);
}

[[noreturn]] void IMU::thread1Func(){
	for(;;){
		if(xSemaphoreTake(sem1, portMAX_DELAY) != pdTRUE) continue;

		lsm6ds3tr_c_all_sources_t src;
		lsm6ds3tr_c_all_sources_get(&ctx, &src);

		uint8_t fifoThresh = 0;
		lsm6ds3tr_c_fifo_wtm_flag_get(&ctx, &fifoThresh);

		if(fifoThresh){
			uint16_t numReadings;
			lsm6ds3tr_c_fifo_data_level_get(&ctx, &numReadings);
			const auto numDataSets = numReadings / 6;

			struct RawSample { uint16_t gX, gY, gZ, aX, aY, aZ; } buf[numDataSets];
			lsm6ds3tr_c_fifo_raw_data_get(&ctx, reinterpret_cast<uint8_t*>(buf), numReadings * 2);

			auto xlConv = [](int16_t raw){ return (double) lsm6ds3tr_c_from_fs16g_to_mg(raw) / 1000.0; };
			auto gyConv = [](int16_t raw){ return ((double) lsm6ds3tr_c_from_fs2000dps_to_mdps(raw) * M_PI / 180.0) / 1000.0; };

			for(auto& read : buf){
				Sample sample = {
					gyConv(read.gX),
					gyConv(read.gY),
					gyConv(read.gZ),
					xlConv(read.aX),
					xlConv(read.aY),
					xlConv(read.aZ)
				};

				fifoSamples.post(sample);
			}

			Event evt = { .action = Event::FIFO };
			Events::post(Facility::Motion, &evt, sizeof(evt));
		}

		if(src.func_src1.sign_motion_ia){
			Event evt = { .action = Event::SignMotion };
			Events::post(Facility::Motion, &evt, sizeof(evt));
		}

		if(src.tap_src.single_tap){
			Event evt = { .action = Event::SingleTap };
			Events::post(Facility::Motion, &evt, sizeof(evt));
		}

	}
}

[[noreturn]] void IMU::thread2Func(){
	for(;;){
		if(xSemaphoreTake(sem2, portMAX_DELAY) != pdTRUE) continue;

		lsm6ds3tr_c_all_sources_t src;
		lsm6ds3tr_c_all_sources_get(&ctx, &src);

		bool ypos = (tiltDirection == TiltDirection::Lifted) ^ (position == WatchPosition::FaceUp);
		if((src.wrist_tilt_ia.wrist_tilt_ia_ypos && ypos) || (src.wrist_tilt_ia.wrist_tilt_ia_yneg && !ypos)){
			Event evt = { .action = Event::WristTilt };
			Events::post(Facility::Motion, &evt, sizeof(evt));
		}
	}
}

void IMU::enableGyroAccelero(bool enable){
	clearFifo();
	fifoSamples.reset();

	if(enable){
		lsm6ds3tr_c_fifo_mode_set(&ctx, LSM6DS3TR_C_STREAM_MODE);
	}else{
		lsm6ds3tr_c_fifo_mode_set(&ctx, LSM6DS3TR_C_BYPASS_MODE);
	}
}

void IMU::setTiltDirection(IMU::TiltDirection direction){
	this->tiltDirection = direction;
	//XOR - tilt logic is inverted if WristPosition is FaceUp
	bool ypos = (tiltDirection == TiltDirection::Lifted) ^ (position == WatchPosition::FaceUp);
	lsm6ds3tr_c_a_wrist_tilt_mask_t tiltMask = { 0, 0, 0, !ypos, ypos, 0, 0 };
	lsm6ds3tr_c_tilt_src_set(&ctx, &tiltMask);
}

void IMU::setWristPosition(WatchPosition wristPosition){
	this->position = wristPosition;
	bool ypos = (tiltDirection == TiltDirection::Lifted) ^ (position == WatchPosition::FaceUp);
	lsm6ds3tr_c_a_wrist_tilt_mask_t tiltMask = { 0, 0, 0, !ypos, ypos, 0, 0 };
	lsm6ds3tr_c_tilt_src_set(&ctx, &tiltMask);
}

void IMU::enableMotionDetection(bool enable){
	lsm6ds3tr_c_motion_sens_set(&ctx, enable);
}
