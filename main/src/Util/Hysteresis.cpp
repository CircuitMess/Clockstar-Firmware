#include "Hysteresis.h"

Hysteresis::Hysteresis(std::initializer_list<int> thresholds, int margin) : Thresholds(thresholds),
																			LevelCount(thresholds.size() - 1),
																			Margin(margin),
																			currentLevel(0){



}

int Hysteresis::get() const{
	if(currentLevel < 0) return 0;
	else if(currentLevel >= LevelCount) return LevelCount-1;
	return currentLevel;
}

int Hysteresis::update(int val){
	int lb = Thresholds[currentLevel];
	if(currentLevel > 0) lb -= Margin;   // subtract margin

	int ub = Thresholds[currentLevel + 1];
	if(currentLevel < LevelCount) ub += Margin;  // add margin

	// now test if input is between the outer margins for current output value
	if(val < lb || val > ub){
		// determine new output level by scanning endPointInput array
		currentLevel = findLevel(val);
	}

	return get();
}

int Hysteresis::reset(int val){
	currentLevel = findLevel(val);
	return get();
}

int Hysteresis::findLevel(int val){
	int i;
	for(i = 0; i < LevelCount; i++){
		if(val >= Thresholds[i] && val <= Thresholds[i + 1]) break;
	}
	return i;
}
