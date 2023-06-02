#include "IMU.h"
#include <freertos/task.h>
#include <esp_log.h>
#include <driver/gpio.h>

static const char* tag = "IMU";

IMU::IMU(I2C& i2c) : i2c(i2c), rawReads(MaxReads), thread1([this](){ thread1Func(); }, "IMU_INT1"), thread2([this](){ thread2Func(); }, "IMU_INT2"){
	ctx = {
			.write_reg = platform_write,
			.read_reg = platform_read,
			.mdelay = delayMillis,
			.handle = this
	};
}

bool IMU::init(){
	uint8_t id;
	lsm6ds3tr_c_device_id_get(&ctx, &id);
	if(id != LSM6DS3TR_C_ID) return false;

	lsm6ds3tr_c_block_data_update_set(&ctx, 1); //for reading 2 byte long values

	//accelero setup
	lsm6ds3tr_c_xl_filter_analog_set(&ctx, LSM6DS3TR_C_XL_ANA_BW_400Hz);
	lsm6ds3tr_c_xl_full_scale_set(&ctx, LSM6DS3TR_C_16g);
	lsm6ds3tr_c_xl_data_rate_set(&ctx, LSM6DS3TR_C_XL_ODR_104Hz);

	//gyro setup
	lsm6ds3tr_c_gy_data_rate_set(&ctx, LSM6DS3TR_C_GY_ODR_104Hz);
	lsm6ds3tr_c_gy_full_scale_set(&ctx, LSM6DS3TR_C_2000dps);

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


	lsm6ds3tr_c_pin_int1_route_set(&ctx, { 0, 0, 0, 1, 0, 0, 1, 0, 0, 0, 0, 1, 0, 0, 1, 0, 0, 0 });
	gpio_config_t io_conf = {};
	io_conf.intr_type = GPIO_INTR_POSEDGE;
	io_conf.pin_bit_mask = (1ULL << IMU_INT1);
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
	gpio_config(&io_conf);
//	gpio_wakeup_enable(static_cast<gpio_num_t>(IMU_INT1), GPIO_INTR_HIGH_LEVEL);
	gpio_install_isr_service(0);

	isrArgs1 = std::make_shared<ISRArgs>(IMU_INT1, this);

	lsm6ds3tr_c_pin_int2_route_set(&ctx, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1 }); //wrist tilt to INT2
	io_conf.pin_bit_mask = (1ULL << IMU_INT2);
	gpio_config(&io_conf);
//	gpio_wakeup_enable(static_cast<gpio_num_t>(IMU_INT2), GPIO_INTR_HIGH_LEVEL);
	isrArgs2 = std::make_shared<ISRArgs>(IMU_INT2, this);

	sem1 = xSemaphoreCreateBinary();
	sem2 = xSemaphoreCreateBinary();

	thread1.start();
	thread2.start();


	gpio_isr_handler_add(static_cast<gpio_num_t>(IMU_INT1), gpio_isr_handler, (void*) isrArgs1.get());
	gpio_isr_handler_add(static_cast<gpio_num_t>(IMU_INT2), gpio_isr_handler, (void*) isrArgs2.get());


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

void IMU::delayMillis(uint32_t millis){
	vTaskDelay(millis);
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

void IMU::thread1Func(){
	for(;;){
		if(xSemaphoreTake(sem1, portMAX_DELAY)){

			lsm6ds3tr_c_all_sources_t src;
			lsm6ds3tr_c_all_sources_get(&ctx, &src);

			uint8_t fifoThresh = 0;
			lsm6ds3tr_c_fifo_wtm_flag_get(&ctx, &fifoThresh);

			if(fifoThresh){
				uint16_t numReadings;
				lsm6ds3tr_c_fifo_data_level_get(&ctx, &numReadings);
				Events::post(Facility::FIFO, nullptr, 0);

				const auto numDataSets = numReadings / 6;
				IMU::GyroAcceleroRaw buf[numDataSets];

				lsm6ds3tr_c_fifo_raw_data_get(&ctx, reinterpret_cast<uint8_t*>(buf), numReadings * 2);

				for(auto& read: buf){
					rawReads.post(read);
				}
			}
			if(src.func_src1.sign_motion_ia){
				Events::post(Facility::SignMotion, nullptr, 0);
			}
			if(src.tap_src.single_tap){
				Events::post(Facility::SingleTap, nullptr, 0);
			}
			if(src.tap_src.double_tap){
				Events::post(Facility::DoubleTap, nullptr, 0);
			}
		}
	}
}

void IMU::thread2Func(){
	for(;;){
		if(xSemaphoreTake(sem2, portMAX_DELAY)){

			lsm6ds3tr_c_all_sources_t src;
			lsm6ds3tr_c_all_sources_get(&ctx, &src);

			if(src.wrist_tilt_ia.wrist_tilt_ia_yneg){
				Events::post(Facility::WristTilt, nullptr, 0);
			}
		}
	}
}

Queue<IMU::GyroAcceleroRaw>& IMU::getRawReads(){
	return rawReads;
}

void IMU::enableGyroAccelero(bool enable){
	clearFifo();
	rawReads.reset();

	if(enable){
		lsm6ds3tr_c_fifo_mode_set(&ctx, LSM6DS3TR_C_STREAM_MODE);
	}else{
		lsm6ds3tr_c_fifo_mode_set(&ctx, LSM6DS3TR_C_BYPASS_MODE);
	}
}

void IMU::setTiltDirection(IMU::TiltDirection direction){
	this->tiltDirection = direction;
	//XOR - tilt logic is inverted if WristPosition is FaceDown
	bool ypos = (tiltDirection == TiltDirection::Lifted) ^ (position == WatchPosition::FaceDown);
	lsm6ds3tr_c_a_wrist_tilt_mask_t tiltMask = { 0, 0, 0, !ypos, ypos, 0, 0 };
	lsm6ds3tr_c_tilt_src_set(&ctx, &tiltMask);
}

void IMU::setWristPosition(WatchPosition wristPosition){
	this->position = wristPosition;
	bool ypos = (tiltDirection == TiltDirection::Lifted) ^ (position == WatchPosition::FaceDown);
	lsm6ds3tr_c_a_wrist_tilt_mask_t tiltMask = { 0, 0, 0, !ypos, ypos, 0, 0 };
	lsm6ds3tr_c_tilt_src_set(&ctx, &tiltMask);
}

void IMU::enableMotionDetection(bool enable){
	lsm6ds3tr_c_motion_sens_set(&ctx, enable);
}
