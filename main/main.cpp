#include <Clockstar.h>

void init();

extern "C" void app_main(void){
	init();
}

void init(){
	Clockstar.begin();

}