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
	uint16_t duration; //[ms]
};

typedef std::vector<Chirp> Sound;

/**
 * Simple Audio system designed for short SFX played on a simple piezo buzzer.
 */
class ChirpSystem : private Threaded {
public:
	explicit ChirpSystem(PWM& pwm);
	virtual ~ChirpSystem();
	/**
	 * Plays the specified sound, interrupts the currently playing sound.
	 */
	void playFromISR(std::initializer_list<Chirp> sound);
	void playFromISR(const Sound& sound);

	void play(std::initializer_list<Chirp> sound);
	void play(const Sound& sound);

	void stopFromISR();
	void stop();

	void setMute(bool mute);
	[[nodiscard]] bool isMuted() const;


private:
	PWM& pwm;
	bool mute = false;

	void loop() override;
	void processClearTone(uint16_t numToClear);
	QueueHandle_t queue;
	SemaphoreHandle_t timerSem;

	Timer timer;
	static void isr(void* arg);

	static constexpr long freqMap(long val, long fromLow, long fromHigh, long toLow, long toHigh);
	static constexpr uint32_t DRAM_ATTR MaxLength = 10000; //10s
	static constexpr uint32_t DRAM_ATTR MinimumLength = 5; //5ms
	static constexpr uint32_t DRAM_ATTR QueueLength = MaxLength / MinimumLength;

	struct Tone {
		uint16_t freq; //Hz
		uint16_t length; //ms
	};
	struct QueueItem {
		enum class Type : uint8_t {
			Tone, ClearTones
		} type;
		union Data {
			Tone tone;
			uint16_t numToClear;
		} data;
	};
};

#endif //CIRCUITMESS_AUDIO_AUDIOSYSTEM_H
