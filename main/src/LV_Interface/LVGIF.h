#ifndef LVGL_CPP_LVGIF_H
#define LVGL_CPP_LVGIF_H

#include "LVObject.h"
#include <vector>
#include <functional>

/**
 * For GIFs converted using LVGL GIF converter (https://github.com/CircuitMess/LVGL_GIFConverter)
 */
class LVGIF : public LVObject {
public:
	LVGIF(lv_obj_t* parent, const char* path);
	~LVGIF() override;

	enum class LoopType {
		Single, // play only one loop
		On // loop indefinitely
	};

	void start();
	void stop();
	void reset();
	void setLooping(LoopType loop);
	void setDoneCallback(std::function<void()> cb);
	void setImage(size_t index);
	[[nodiscard]] size_t getNumFrames() const;

private:
	lv_obj_t* img;
	lv_timer_t* timer;

	uint16_t w = 0, h = 0;
	std::vector<uint16_t> durations; //in ms
	uint32_t index = 0;

	const char* path;
	uint32_t pathLen = 0;
	char* imgPath;

	LoopType loopType = LoopType::On;
	std::function<void()> cb;
};


#endif //LVGL_CPP_LVGIF_H
