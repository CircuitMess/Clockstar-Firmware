#include "Hysteresis.h"

Hysteresis::Hysteresis(std::initializer_list<Threshold> thresholds) : thresholds(thresholds){

}

int Hysteresis::get() const{
	return discrete_level;
}

int Hysteresis::update(int val){
	if(val >= prev_val){
		discrete_level = 0;
		for(auto threshold : thresholds){
			if(val >= threshold.high){
				discrete_level = threshold.level;
			}
		}
	}else{
		discrete_level = thresholds[thresholds.size() - 1].level;
		for(int i = 0; i < thresholds.size(); i++){
			if(val <= thresholds[thresholds.size() - 1 - i].low){
				discrete_level = thresholds[thresholds.size() - 1 - i].level - 1;
			}
		}
	}

	prev_val = val;

	return get();
}

void Hysteresis::reset(int toVal){
	prev_val = toVal;
	update(toVal);
}
