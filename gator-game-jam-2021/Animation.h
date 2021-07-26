#pragma once

#include <vector>
#include "TickClock.h"
#include "Image.h"

class Animation
{
private:
	std::vector<Image> frames_;
	TickClock frameClock_;
	unsigned int currentFrameIndex_;
public:
	Animation(const std::vector<Image> &frames, float frameSecs);
	Animation(
		ALLEGRO_BITMAP *sheet,
		unsigned int sheetX, unsigned int sheetY,
		unsigned char frameWidth, unsigned char frameHeight,
		unsigned int numFrames,
		float frameSecs);

	void updateOnTick();

	void reset();

	const Image &currentFrame() const;
};