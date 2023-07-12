#include <esp_log.h>
#include "ChirpSystem.h"
#include "Util/stdafx.h"

static const char* TAG = "ChirpSystem";

ChirpSystem::ChirpSystem(PWM& pwm) : Threaded("ChirpSystem", 2048, UINT8_MAX, 0), pwm(pwm), sem(xSemaphoreCreateBinary()), timer(MinimumLength * 1000, isr, sem){
}

ChirpSystem::~ChirpSystem(){
	stop();
	Threaded::stop();
	vSemaphoreDelete(sem);
}

void ChirpSystem::play(std::initializer_list<Chirp> sound){
	play((Sound) sound);
}

void ChirpSystem::play(const Sound& sound){
	if(mute) return;

	uint32_t totalLength = 0;
	for(const Chirp& chirp : sound){
		totalLength += chirp.duration;
	}
	if(totalLength > MaxLength){
		ESP_LOGE(TAG, "Sound is too long! Max length is %lums, sound is %lums", MaxLength, totalLength);
		return;
	}
	stop();

	std::fill(tones.begin(), tones.end(), Tone{ 0, 0 });
	toneIndex = 0;

	uint32_t index = 0;
	for(const Chirp& chirp : sound){
		if(chirp.endFreq == chirp.startFreq){
			tones[index++] = { chirp.startFreq, chirp.duration };
			continue;
		}
		//TODO - group tones with a low  frequency delta, this would reduce the number of discrete tones
		for(uint32_t durationSum = 0; durationSum < chirp.duration;){
			auto freq = freqMap((long) durationSum, 0, chirp.duration, chirp.startFreq, chirp.endFreq);
			auto tonePeriod = std::max(MinimumLength, (uint32_t) (1000.0 / (double) freq));
			auto constrainedTonePeriod = std::min(tonePeriod, chirp.duration - durationSum);

			if(!PWM::checkFrequency(freq)){
				freq = 0;
			}
			tones[index++] = { (uint32_t) freq, constrainedTonePeriod };
			durationSum += constrainedTonePeriod;
		}
	}

	timer.reset();
	timer.setPeriod(tones[0].length);
	start();
	timer.start();
}

void ChirpSystem::stop(){
	timer.stop();
	pwm.stop();
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

void IRAM_ATTR ChirpSystem::isr(void* arg){
	BaseType_t xHigherPriorityTaskWoken = pdTRUE;
	xSemaphoreGiveFromISR(arg, &xHigherPriorityTaskWoken);
}

void ChirpSystem::loop(){
	if(xSemaphoreTake(sem, portMAX_DELAY)){
		auto tone = tones[toneIndex++];

		if(tone.length == 0){
			stop();
			return;
		}

		if(tone.freq == 0){
			pwm.stop();
		}else{
			pwm.setFreq(tone.freq);
		}

		timer.setPeriod(tone.length);
	}
}

constexpr long ChirpSystem::freqMap(long val, long fromLow, long fromHigh, long toLow, long toHigh){
	return (val - fromLow) * (toHigh - toLow) / (fromHigh - fromLow) + toLow;
}
