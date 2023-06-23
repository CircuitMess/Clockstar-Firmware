#include "EMA.h"

EMA::EMA(double a) : a(a){

}

double EMA::get(){
	return val;
}

double EMA::update(double val){
	this->val = this->val * (1.0 - a) + a * val;
	return get();
}

void EMA::reset(double toVal){
	val = toVal;
}
