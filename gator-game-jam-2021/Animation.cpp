#include "Animation.h"

Animation::Animation(const std::vector<Image> &frames, float frameSecs) :
	frames_(frames),
	frameClock_(frameSecs),
	currentFrameIndex_(0)
{}

Animation::Animation(
	ALLEGRO_BITMAP *sheet,
	unsigned int sheetX, unsigned int sheetY,
	unsigned char frameWidth, unsigned char frameHeight,
	unsigned int numFrames,
	float frameSecs)
	:
	frameClock_(frameSecs),
	currentFrameIndex_(0)
{
	for (unsigned int i = 0; i < numFrames; i++)
		frames_.push_back(
			Image(
				sheet,
				sheetX + frameWidth * i, sheetY,
				frameWidth, frameHeight));
}

void Animation::updateOnTick()
{
	frameClock_.updateOnTick();

	if (frameClock_.isDone())
	{
		frameClock_.reset();
		if (++currentFrameIndex_ >= frames_.size())
			currentFrameIndex_ = 0;
	}
}

void Animation::reset()
{
	frameClock_.reset();
	currentFrameIndex_ = 0;
}

const Image &Animation::currentFrame() const
{
	return frames_.at(currentFrameIndex_);
}