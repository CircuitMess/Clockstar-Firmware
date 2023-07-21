#include "LEDController.h"

template <typename T>
LEDController<T>::LEDController() : Threaded("LEDController", 2048, 6), timerSem(xSemaphoreCreateBinary()),
									timer(1 /*placeholder*/, isr, timerSem){

}

template <typename T>
LEDController<T>::~LEDController(){
	end();
}

template <typename T>
void LEDController<T>::begin(){
	init();
	clear();
	start();
	timer.start();
}

template <typename T>
void LEDController<T>::end(){
	timer.stop();
	clear();
	stop(0);
	abortFlag = true;
	xSemaphoreGive(timerSem);
	while(running()){
		vTaskDelay(1);
	}
	deinit();
}

template <typename T>
void LEDController<T>::clear(){
	timer.stop();
	std::unique_lock lock(mut);

	shortAction = {};
	shortAction.type = ShortAction::None;
	continuousAction = {};
	continuousAction.type = ContinuousAction::None;
	write(T());
}

template <typename T>
void LEDController<T>::setSolid(T color){
	std::unique_lock lock(mut);
	continuousAction = { .type = ContinuousAction::Solid, .state = ContinuousAction::Pending, .data = { .solidColor = color } };
	if(shortAction.type == ShortAction::None){
		xSemaphoreGive(timerSem);
	}
}

template <typename T>
void LEDController<T>::blink(T color, uint32_t onTime, uint32_t offTime){
	std::unique_lock lock(mut);
	shortAction = { ShortAction::BlinkOnce, ShortAction::Pending, onTime, offTime, color };
	xSemaphoreGive(timerSem);

}

template <typename T>
void LEDController<T>::blinkTwice(T color, uint32_t onTime, uint32_t offTime){
	std::unique_lock lock(mut);
	shortAction = { ShortAction::BlinkTwice, ShortAction::Pending, onTime, offTime, color };
	xSemaphoreGive(timerSem);

}

template <typename T>
void LEDController<T>::blinkContinuous(T color, int32_t loops, uint32_t onTime, uint32_t offTime){
	std::unique_lock lock(mut);

	if(continuousAction.type == ContinuousAction::ContinuousBlink &&
	   continuousAction.data.continuousBlink.onTime == onTime &&
	   continuousAction.data.continuousBlink.offTime == offTime &&
	   continuousAction.data.continuousBlink.loops == loops &&
	   continuousAction.data.continuousBlink.color == color)
		return;

	continuousAction = { ContinuousAction::ContinuousBlink, ContinuousAction::Pending, { .continuousBlink = { color, onTime, offTime, loops, 0 } } };
	if(shortAction.type == ShortAction::None){
		xSemaphoreGive(timerSem);
	}
}

template <typename T>
void LEDController<T>::breathe(T start, T end, size_t period, int32_t loops){
	std::unique_lock lock(mut);

	if(continuousAction.type == ContinuousAction::Breathe &&
	   continuousAction.data.breathe.start == start && continuousAction.data.breathe.end == end &&
	   continuousAction.data.breathe.period == period &&
	   continuousAction.data.breathe.loops == loops)
		return;

	continuousAction = { ContinuousAction::Breathe, ContinuousAction::Pending, { .breathe = { start, end, period, loops, 0, 0 } } };
	if(shortAction.type == ShortAction::None){
		xSemaphoreGive(timerSem);
	}
}

template <typename T>
void LEDController<T>::loop(){
	while(!xSemaphoreTake(timerSem, portMAX_DELAY));

	if(abortFlag) return;

	timer.stop();

	std::unique_lock lock(mut);

	auto timerPeriod = handleShortAction();
	if(timerPeriod == 0){
		timerPeriod = handleContinuousAction();
	}
	lock.unlock();

	if(timerPeriod == 0) return;

	timer.setPeriod(timerPeriod);
	timer.reset();
	timer.start();
}

template <typename T>
uint32_t LEDController<T>::handleContinuousAction(){
	auto timerVal = 0;

	if(continuousAction.type == ContinuousAction::None){
		return 0;
	}else if(continuousAction.type == ContinuousAction::Solid){
		if(continuousAction.state == ContinuousAction::Pending || continuousAction.state == ContinuousAction::On){
			write(continuousAction.data.solidColor);
			continuousAction.state = ContinuousAction::On;
		}
	}else if(continuousAction.type == ContinuousAction::ContinuousBlink){
		switch(continuousAction.state){
			case ContinuousAction::Pending:
				write(continuousAction.data.continuousBlink.color);
				timerVal = continuousAction.data.continuousBlink.onTime;
				continuousAction.state = ContinuousAction::On;
				break;
			case ContinuousAction::On:
				write(T());
				timerVal = continuousAction.data.continuousBlink.offTime;
				continuousAction.state = ContinuousAction::Off;
				break;
			case ContinuousAction::Off:
				continuousAction.data.continuousBlink.currLoops++;
				if(continuousAction.data.continuousBlink.loops == -1 ||
				   continuousAction.data.continuousBlink.currLoops < continuousAction.data.continuousBlink.loops){
					write(continuousAction.data.continuousBlink.color);
					timerVal = continuousAction.data.continuousBlink.onTime;
					continuousAction.state = ContinuousAction::On;
				}else{
					timerVal = 0;
					continuousAction.type = ContinuousAction::None;
				}
				break;
		}
	}else if(continuousAction.type == ContinuousAction::Breathe){
		switch(continuousAction.state){
			case ContinuousAction::Pending:
				write(continuousAction.data.breathe.start);
				timerVal = BreatheDeltaT;
				continuousAction.data.breathe.t += BreatheDeltaT;
				continuousAction.state = ContinuousAction::On;
				break;
			case ContinuousAction::On:
				continuousAction.data.breathe.currLoops++;
				if(continuousAction.data.breathe.loops == -1 ||
				   continuousAction.data.breathe.currLoops < continuousAction.data.breathe.loops){
					float t = 0.5 * cos(2 * M_PI * continuousAction.data.breathe.t / continuousAction.data.breathe.period) + 0.5;
					T startPart = continuousAction.data.breathe.start;
					startPart *= t;
					T endPart = continuousAction.data.breathe.end;
					endPart *= (1.0f - t);
					write(startPart + endPart);
					timerVal = BreatheDeltaT;
					continuousAction.data.breathe.t += BreatheDeltaT;
				}else{
					timerVal = 0;
					continuousAction.type = ContinuousAction::None;
				}
				break;
			case ContinuousAction::Off:
				continuousAction.type = ContinuousAction::None;
				timerVal = 0;
		}

	}

	return timerVal;
}

template <typename T>
uint32_t LEDController<T>::handleShortAction(){
	auto timerVal = 0;

	if(shortAction.type == ShortAction::None) return 0;

	else if(shortAction.type == ShortAction::BlinkOnce){
		switch(shortAction.state){
			case ShortAction::Pending:
				write(shortAction.color);
				timerVal = shortAction.onTime;
				shortAction.state = ShortAction::On;
				break;
			case ShortAction::On:
				write(T());
				timerVal = shortAction.offTime;
				shortAction.state = ShortAction::Off;
				break;
			case ShortAction::Off:
				timerVal = 0;
				shortAction.type = ShortAction::None;
				break;
		}
	}else if(shortAction.type == ShortAction::BlinkTwice){
		switch(shortAction.state){
			case ShortAction::Pending:
				timerVal = shortAction.onTime;
				write(shortAction.color);
				shortAction.state = ShortAction::On;
				break;
			case ShortAction::On:
				write(T());
				timerVal = shortAction.offTime;
				shortAction.state = ShortAction::Off;
				break;
			case ShortAction::Off:
				write(shortAction.color);
				timerVal = shortAction.onTime;
				shortAction.type = ShortAction::BlinkOnce;
				shortAction.state = ShortAction::On;
				break;
		}
	}

	return timerVal;
}

template <typename T>
void LEDController<T>::isr(void* arg){
	BaseType_t priority = pdFALSE;
	xSemaphoreGiveFromISR(arg, &priority);
}


template
class LEDController<uint8_t>;

SingleLEDController::SingleLEDController(PWM& pwm) : pwm(pwm){}

void SingleLEDController::init(){
}

void SingleLEDController::deinit(){

}

void SingleLEDController::write(uint8_t val){
	double fVal = (float) val / 255.0f;
	fVal = std::pow(fVal, 2);
	fVal = std::round(fVal * 255.0f);
	fVal = fVal * 100.0 / 255.0;
	pwm.setDuty((uint8_t) fVal);
}


template
class LEDController<glm::vec3>;

RGBLEDController::RGBLEDController(PWM& pwmR, PWM& pwmG, PWM& pwmB) : pwmR(pwmR), pwmG(pwmG), pwmB(pwmB){}

void RGBLEDController::init(){


}

void RGBLEDController::deinit(){

}

void RGBLEDController::write(glm::vec3 val){
	val *= 100;
	val /= 255.0;

	pwmR.setDuty(val.x);
	pwmG.setDuty(val.y);
	pwmB.setDuty(val.z);
}
