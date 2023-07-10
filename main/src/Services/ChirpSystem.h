#ifndef CIRCUITMESS_AUDIO_AUDIOSYSTEM_H
#define CIRCUITMESS_AUDIO_AUDIOSYSTEM_H

#include "../Util/Threaded.h"
#include <mutex>
#include "../Periph/PWM.h"
#include "Periph/Timer.h"
#include <array>

/**
 * A chirp is a waveform that “sweeps” from a starting frequency to an ending frequency, during the specified duration of time.
 * Using PWM this is simulated by playing discrete frequencies in sequence.
 */
struct Chirp {
	uint16_t startFreq; //[Hz]
	uint16_t endFreq; //[Hz]
	uint32_t duration; //[ms]
};

typedef std::vector<Chirp> Sound;

/**
 * Simple Audio system designed for short SFX played on a simple piezo buzzer.
 */
class ChirpSystem {
public:
	explicit ChirpSystem(PWM& pwm);
	virtual ~ChirpSystem();
	/**
	 * Plays the specified sound, interrupts the currently playing sound.
	 */
	void play(std::initializer_list<Chirp> sound);
	void play(const Sound& sound);

	void stop();

	void setMute(bool mute);
	[[nodiscard]] bool isMuted() const;


private:
	PWM& pwm;
	bool mute = false;
	Timer timer;

	static void isr(void* arg);

	static constexpr long freqMap(long val, long fromLow, long fromHigh, long toLow, long toHigh);
	static constexpr uint32_t MaxLength = 10000; //10s
	static constexpr uint32_t MinimumLength = 5; //5ms
	struct Tone {
		uint32_t freq; //Hz
		uint32_t length; //ms
	};
	std::array<Tone, MaxLength / MinimumLength> tones{};
	volatile uint32_t toneIndex = 0;
};

#endif //CIRCUITMESS_AUDIO_AUDIOSYSTEM_H
