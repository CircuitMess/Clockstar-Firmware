#include "LEDController.h"
#include "Util/stdafx.h"

template <typename T>
LEDController<T>::LEDController() : Threaded("LEDController", 2048, 6){

}

template <typename T>
void LEDController<T>::begin(){
	init();
	clear();
	start();
}

template <typename T>
void LEDController<T>::end(){
	stop();
	clear();
	deinit();
}

template <typename T>
void LEDController<T>::setValue(T color){
	LEDcolor = color;

	if(LEDstate == Solid){
		write(color);
	}
}

template <typename T>
void LEDController<T>::clear(){
	LEDstate = Solid;
	blinkState = false;
	blinkColor = T();
	blinkStartTime = 0;
	LEDcolor = T();
	breatheQueued = false;

	write(LEDcolor);
}

template <typename T>
void LEDController<T>::setSolid(T color){
	LEDstate = Solid;
	setValue(color);
}

template <typename T>
void LEDController<T>::blink(T color){
	LEDstate = Once;
	blinkColor = color;
	blinkStartTime = millis();
	blinkState = true;

	write(color);
}

template <typename T>
void LEDController<T>::blinkTwice(T color){
	blink(color);
	LEDstate = Twice;
}

template <typename T>
void LEDController<T>::blinkContinuous(T color, uint32_t duration){
	blink(color);
	blinkContinuousDuration = duration;
	LEDstate = Continuous;
}

template <typename T>
void LEDController<T>::breathe(T start, T end, size_t period, int16_t loops){
	if(loops == 0) return;

	if(LEDstate == Breathe && breathePeriod == period && breatheStart == start && breatheEnd == end){
		return;
	}

	breathePeriod = period;
	breatheLoops = loops;
	breatheStart = start;
	breatheEnd = end;
	breatheLoopCounter = 0;
	breatheMillis = millis();

	if(LEDstate == Once || LEDstate == Twice){
		//can't interrupt blinking with breathe command
		breatheQueued = true;
		return;
	}

	LEDstate = Breathe;
	write(breatheStart);
}

template <typename T>
void LEDController<T>::loop(){
	vTaskDelay(1);
	if(LEDstate == Solid) return;
	else if(LEDstate == Twice || LEDstate == Once){
		if(millis() - blinkStartTime < blinkDuration) return;
	}else if(LEDstate == Continuous){
		if(millis() - blinkStartTime < blinkContinuousDuration) return;
	}

	bool push = false;
	T pushVal{};

	if(LEDstate == Continuous){
		blinkState = !blinkState;
		blinkStartTime = millis();
		pushVal = blinkState ? blinkColor : T();
		push = true;
	}else if(LEDstate == Twice && blinkState){
		blinkState = false;
		blinkStartTime = millis();
		pushVal = T();
		push = true;
	}else if(LEDstate == Twice && !blinkState){
		blinkState = true;
		blinkStartTime = millis();
		LEDstate = Once;
		pushVal = blinkColor;
		push = true;
	}else if(LEDstate == Once){
		blinkState = false;
		blinkStartTime = 0;
		blinkColor = T();

		if(breatheQueued){
			LEDstate = Breathe;
		}else{
			LEDstate = Solid;
		}

		pushVal = LEDcolor;
		push = true;
	}else if(LEDstate == Breathe){
		if(millis() - breatheMillis >= breathePeriod){
			breatheMillis = millis();
			if(breatheLoops != -1){
				breatheLoopCounter++;
				if(breatheLoopCounter >= breatheLoops){
					LEDstate = Solid;
					pushVal = LEDcolor;
					write(pushVal);
					return;
				}
			}
		}
		push = true;

		float t = 0.5 * cos(2 * M_PI * (millis() - breatheMillis) / breathePeriod) + 0.5;

		T startPart = breatheStart;
		startPart *= t;
		T endPart = breatheEnd;
		endPart *= (1.0f - t);
		pushVal = startPart + endPart;

	}

	if(push){
		write(pushVal);
	}
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
	pwmR.setDuty(val.x);
	pwmG.setDuty(val.y);
	pwmB.setDuty(val.z);
}
