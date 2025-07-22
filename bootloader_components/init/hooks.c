#include "esp_attr.h"
#include "hal/gpio_hal.h"
#include "hal/efuse_ll.h"
#include "esp_log.h"

static const char* TAG = "hook";

/** Function used to tell the linker to include this file with all its symbols. */
void bootloader_hooks_include(void){}

void readEfuse(uint16_t* PID, uint8_t* Revision){
	/**
	 * Reading is done using raw register reads.
	 * Using the 'efuse' component results in crashes (TG0WDT_SYS_RST) !!!
	 *
	 * Block 3 = User block
	 * 00 00 XX YY | ZZ 00 00 00
	 * XX - lower byte of PID
	 * YY - upper byte of PID
	 * ZZ - Revision byte
	 */

	//Byteswapping is applied to have the same appearance as in 'espefuse summary' (v4.8.1)
	uint32_t reg = REG_READ(EFUSE_RD_USR_DATA0_REG);
	uint32_t reversedReg = (((reg) & 0xff000000) >> 24) | (((reg) & 0x00ff0000) >> 8) | (((reg) & 0x0000ff00) << 8) | (((reg) & 0x000000ff) << 24);
	uint16_t readPID = ((reversedReg & 0xFF00) >> 8 )| ((reversedReg & 0xFF) << 8);

	reg =  REG_READ(EFUSE_RD_USR_DATA1_REG);
	reversedReg = (((reg) & 0xff000000) >> 24) | (((reg) & 0x00ff0000) >> 8) | (((reg) & 0x0000ff00) << 8) | (((reg) & 0x000000ff) << 24);
	uint8_t readRevision = ((reversedReg & 0xFF000000) >> 24);

	ESP_LOGI(TAG, "PID: %d, rev: %d", readPID, readRevision);

	*PID = readPID;
	*Revision = readRevision;
}

void IRAM_ATTR bootloader_before_init(void){
	/* Keep in my mind that a lot of functions cannot be called from here
	 * as system initialization has not been performed yet, including
	 * BSS, SPI flash, or memory protection. */
	// ESP_LOGI("HOOK", "This hook is called BEFORE bootloader initialization");


	//WARNING - proceed with caution around PWDN (powerdown) pin!
	//Setting it to low (0) during bootloader WILL brick the device!

	uint8_t Revision = 0;
	uint16_t PID = 0;
	gpio_num_t BacklightLED;

	readEfuse(&PID, &Revision);

	if(PID == 0 && Revision == 0){
		BacklightLED = GPIO_NUM_9;
		ESP_LOGI(TAG, "Unfused Rev2 assumed from bootloader");
	}else if(Revision == 2){
		BacklightLED = GPIO_NUM_9;
		ESP_LOGI(TAG, "Rev2 from bootloader");
	}else{
		ESP_LOGI(TAG, "Rev1 from bootloader");
		gpio_ll_input_enable(&GPIO, GPIO_NUM_13);
		gpio_ll_pulldown_dis(&GPIO, GPIO_NUM_13);
		gpio_ll_pullup_dis(&GPIO, GPIO_NUM_13);

		BacklightLED = GPIO_NUM_4;
	}

	if(BacklightLED != -1){
		gpio_ll_pullup_en(&GPIO, BacklightLED);
		gpio_ll_pulldown_dis(&GPIO, BacklightLED);
		gpio_ll_input_disable(&GPIO, BacklightLED);
		gpio_ll_output_enable(&GPIO, BacklightLED);
		gpio_ll_set_level(&GPIO, BacklightLED, 1);
	}
}

void bootloader_after_init(void){
	// ESP_LOGI("HOOK", "This hook is called AFTER bootloader initialization");
}
