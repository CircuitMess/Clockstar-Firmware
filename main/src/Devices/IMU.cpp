#include "IMU.h"
#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <driver/gpio.h>

#include <utility>
#include "../Pins.hpp"

IMU::IMU(I2C& i2c) : i2c(i2c), thread1([this](){ thread1Func(); }, "IMU_INT1"), thread2([this](){ thread2Func(); }, "IMU_INT2"){
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
//	lsm6ds3tr_c_fifo_watermark_set(&ctx, ReadingsWatermark); //after 100 readings in fifo watermark flags is set to 1
//	lsm6ds3tr_c_fifo_xl_batch_set(&ctx, LSM6DS3TR_C_FIFO_XL_NO_DEC);
//	lsm6ds3tr_c_fifo_gy_batch_set(&ctx, LSM6DS3TR_C_FIFO_GY_NO_DEC);
//	lsm6ds3tr_c_fifo_data_rate_set(&ctx, LSM6DS3TR_C_FIFO_104Hz);


	//wrist tilt interrupt setup
	lsm6ds3tr_c_wrist_tilt_sens_set(&ctx, 1);
	uint8_t tiltLatency = 1; // total latency is tiltLatency * 40ms
	lsm6ds3tr_c_tilt_latency_set(&ctx, &tiltLatency);
	uint8_t tiltThresh = 32; // total thresh is tiltThresh * 15.625mg
	lsm6ds3tr_c_tilt_threshold_set(&ctx, &tiltThresh);
	lsm6ds3tr_c_a_wrist_tilt_mask_t tiltMask = { 0, 0, 0, 1, 0, 0, 0 };
	lsm6ds3tr_c_tilt_src_set(&ctx, &tiltMask);


	//significant motion setup
	lsm6ds3tr_c_motion_sens_set(&ctx, 1);
	uint8_t motionSenseThresh = 255;
	lsm6ds3tr_c_motion_threshold_set(&ctx, &motionSenseThresh);

	//tap setup
	lsm6ds3tr_c_tap_detection_on_x_set(&ctx, 1);
	lsm6ds3tr_c_tap_detection_on_y_set(&ctx, 1);
	lsm6ds3tr_c_tap_detection_on_z_set(&ctx, 1);
	lsm6ds3tr_c_tap_threshold_x_set(&ctx, 0x01);
	lsm6ds3tr_c_tap_dur_set(&ctx, 0);
	lsm6ds3tr_c_tap_quiet_set(&ctx, 3);
	lsm6ds3tr_c_tap_shock_set(&ctx, 3);
	lsm6ds3tr_c_tap_mode_set(&ctx, LSM6DS3TR_C_BOTH_SINGLE_DOUBLE);


	//pedometer setup
	lsm6ds3tr_c_pedo_sens_set(&ctx, 1);
	lsm6ds3tr_c_pedo_step_reset_set(&ctx, 1);
	lsm6ds3tr_c_pedo_step_reset_set(&ctx, 0);


	lsm6ds3tr_c_pin_int1_route_set(&ctx, { 0, 0, 0, 0, 0, 0, /*1*/0, 1, 0, 0, 0, /*1*/0, 0, 0, /*1*/0, 0, 0, 0 }); //fifo threshold interrupt on INT1
	gpio_config_t io_conf = {};
	io_conf.intr_type = GPIO_INTR_POSEDGE;
	io_conf.pin_bit_mask = (1ULL << IMU_INT1);
	io_conf.mode = GPIO_MODE_INPUT;
	io_conf.pull_up_en = GPIO_PULLUP_DISABLE;
	gpio_config(&io_conf);
//	gpio_wakeup_enable(static_cast<gpio_num_t>(IMU_INT1), GPIO_INTR_HIGH_LEVEL);

	isrArgs1 = std::make_shared<ISRArgs>(IMU_INT1, this);

	lsm6ds3tr_c_pin_int2_route_set(&ctx, { 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 1, 0, 0 }); //wrist tilt to INT2
	io_conf.pin_bit_mask = (1ULL << IMU_INT2);
	gpio_config(&io_conf);
//	gpio_wakeup_enable(static_cast<gpio_num_t>(IMU_INT2), GPIO_INTR_HIGH_LEVEL);
	isrArgs2 = std::make_shared<ISRArgs>(IMU_INT2, this);

	sem1 = xSemaphoreCreateBinary();
	sem2 = xSemaphoreCreateBinary();

	thread1.start();
	thread2.start();

//	clearFifo();

	gpio_install_isr_service(0);
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

void IMU::thread1Func(){
	for(;;){
		if(xSemaphoreTake(sem1, portMAX_DELAY)){
			//parse INT1 causes
//			uint16_t numReadings;
//			lsm6ds3tr_c_fifo_data_level_get(&ctx, &numReadings);
//			printf("numreads: %d\n", numReadings);
			printf("step\n");
			if(stepFunc) stepFunc();
//			const auto numDataSets = numReadings / 6;
//			IMU::GyroAcceleroRaw buf[numDataSets];
//
//			lsm6ds3tr_c_fifo_raw_data_get(&ctx, reinterpret_cast<uint8_t*>(buf), numReadings * 2);
//			rawReads.post(args->reads.end(), buf, buf + numDataSets);
		}
	}
}


void IMU::thread2Func(){
	for(;;){
		if(xSemaphoreTake(sem2, portMAX_DELAY)){
			printf("knock\n");
			if(knockFunc) knockFunc();
			//parse INT2 causes
		}
	}
}

void IMU::onKnock(std::function<void()> func){
	knockFunc = std::move(func);
}

void IMU::onStep(std::function<void()> func){
	stepFunc = std::move(func);
}

bool IMU::getXTilt(float* tilt){
	int16_t accel[3];
	auto ret = lsm6ds3tr_c_acceleration_raw_get(&ctx, accel);
	if(ret != 0) return false;

	*tilt = lsm6ds3tr_c_from_fs16g_to_mg(accel[0]) / 1000.0;

	return true;
}
