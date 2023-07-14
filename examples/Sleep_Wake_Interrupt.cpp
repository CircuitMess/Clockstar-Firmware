#include <freertos/FreeRTOS.h>
#include <freertos/task.h>
#include <freertos/semphr.h>
#include <driver/gpio.h>
#include <esp_sleep.h>

/** This crashes. */

#define PIN (34)

SemaphoreHandle_t intSem;

void IRAM_ATTR intISR(void* arg){
	gpio_set_intr_type((gpio_num_t) PIN, GPIO_INTR_POSEDGE); // This makes the interrupt pos-edge after wake config makes it high-level
	xSemaphoreGive(intSem);
}

[[noreturn]] void intHandler(void* arg){
	static int trigs = 0;
	for(;;){
		xSemaphoreTake(intSem, portMAX_DELAY);
		printf("Interrupt triggered %d\n", trigs++);
	}
}

void initInt(){
	gpio_install_isr_service(ESP_INTR_FLAG_LOWMED);
	gpio_isr_handler_add((gpio_num_t) PIN, intISR, nullptr);
}

void initWake(){
	esp_sleep_enable_gpio_wakeup();
	gpio_wakeup_enable((gpio_num_t) PIN, GPIO_INTR_HIGH_LEVEL);
}

void sleep(){
	printf("Going to sleep...\n");
	printf("GPIO is %d\n", gpio_get_level((gpio_num_t) PIN));
	vTaskDelay(100);
	esp_light_sleep_start();
	printf("Awake!\n");
}

void init(){
	// Required on current HW version
	gpio_config_t io_conf_13 = {
			.pin_bit_mask = 1ULL << 13,
			.mode = GPIO_MODE_INPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_DISABLE
	};
	gpio_config(&io_conf_13);

	// Interrupt reporting
	intSem = xSemaphoreCreateBinary();
	TaskHandle_t handlerTask;
	xTaskCreatePinnedToCore(intHandler, "Handler", 4 * 1024, nullptr, 5, &handlerTask, 0);

	// Configure pin
	gpio_config_t io_conf = {
			.pin_bit_mask = 1ULL << PIN,
			.mode = GPIO_MODE_INPUT,
			.pull_up_en = GPIO_PULLUP_DISABLE,
			.pull_down_en = GPIO_PULLDOWN_DISABLE,
			.intr_type = GPIO_INTR_POSEDGE
	};
	gpio_config(&io_conf);
	printf("Configured. GPIO is %d\n", gpio_get_level((gpio_num_t) PIN));

	initWake();
	initInt();
	// gpio_config(&io_conf); // uncomment for workaround

	vTaskDelay(1000);
	sleep();
}

extern "C" void app_main(void){
	init();
	vTaskDelete(nullptr);
}