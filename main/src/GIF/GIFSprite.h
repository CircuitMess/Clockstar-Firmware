#ifndef BIT_FIRMWARE_GIFSPRITE_H
#define BIT_FIRMWARE_GIFSPRITE_H

#include <vector>
#include "Devices/Display.h"
#include "FS/File.h"
#include <experimental/functional>
#include "GIF.h"

class GIFSprite {
public:
	GIFSprite(const File& gifFile);
	virtual ~GIFSprite();
	void loop(uint micros);

	void start();
	void stop();

	/**
	 * Returns a sprite object with gif's framebuffer as the source.
	 * @return
	 */
	Sprite getSprite() const;

	void reset();

	uint16_t getWidth() const;
	uint16_t getHeight() const;

	GIF::LoopMode getLoopMode() const;
	void setLoopMode(GIF::LoopMode loopMode);
	uint32_t getLoopCount() const;

	void setLoopDoneCallback(std::function<void(uint32_t loopCount)> loopDoneCallback);
	void setScale(uint8_t scale);

private:
	GIF gif;
	int16_t x = 0, y = 0;

	uint32_t frameCounter = 0;
	uint32_t loopCount = 0;

	uint8_t scale = 1;

	bool running = false;

	std::function<void(uint32_t loopCount)> loopDoneCallback;
};


#endif //BIT_FIRMWARE_GIFSPRITE_H
