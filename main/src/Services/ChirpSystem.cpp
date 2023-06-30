#include "ChirpSystem.h"
#include "Util/stdafx.h"

ChirpSystem::ChirpSystem(PWM& pwm) : pwm(pwm), task([this](){ playbackFunc(); }, "ChirpSystem", 2048){
}

void ChirpSystem::play(std::initializer_list<Chirp> sound){
	if(mute) return;

	if(!task.running()){
		current = sound;
		startMillis = millis();
		task.start();
	}else{
		mut.lock();
		queued = sound;
		mut.unlock();
	}
}

void ChirpSystem::play(const Sound& sound){
	if(mute) return;

	if(!task.running()){
		current = sound;
		startMillis = millis();
		task.start();
	}else{
		mut.lock();
		queued = sound;
		mut.unlock();
	}
}

void ChirpSystem::stop(){
	task.stop();

	queued.clear();
	pwm.stop();
}

void ChirpSystem::playbackFunc(){
	while(chirpID < current.size()){
		mut.lock();
		if(!queued.empty()){
			current = queued;
			queued.clear();
			chirpID = 0;
			startMillis = millis();
			mut.unlock();
			continue;
		}
		mut.unlock();

		currentMillis = millis() - startMillis;

		uint16_t freq = map(currentMillis, 0, current[chirpID].duration, current[chirpID].startFreq, current[chirpID].endFreq);
		if(freq > 0){
			pwm.setFreq(freq);
			vTaskDelay(pdMS_TO_TICKS(3 + (int) (1000.0 / (double) freq)));
		}else{
			pwm.stop();
		}

		if(current[chirpID].duration > currentMillis) continue;

		startMillis = millis();
		chirpID++;

		if(chirpID >= current.size()){
			mut.lock();
			current = queued;
			queued.clear();
			mut.unlock();
			chirpID = 0;
		}
	}
	pwm.stop();
	task.stop();
}

void ChirpSystem::setMute(bool mute){
	this->mute = mute;
	if(mute){
		stop();
	}
}

bool ChirpSystem::isMuted() const{
	return mute;
}
