#include "ImageButton.h"
#include "Mouse.h"
#include "FontData.h"

ImageButton::ImageButton(
	float x, float y,
	const char *text,
	const ALLEGRO_COLOR &textColor,
	unsigned char textSize,
	const Image &image,
	float scale)
	:
	Boundable(AABB(x, y, image.width() * scale, image.height() * scale)),
	text_(text),
	textColor_(textColor),
	textSize_(textSize),
	image_(image),
	scale_(scale),
	delta_(25),
	isHovered_(false)
{}

void ImageButton::updateOnTick()
{
	if (isHovered_)
	{
		if (delta_ < 250)
		{
			delta_ += 5;
		}
		else
		{
			delta_ = 255;
		}
	}
	else
	{
		if (delta_ > 30)
		{
			delta_ -= 5;
		}
		else
		{
			delta_ = 25;
		}
	}
}

void ImageButton::updateOnMouseAxes(const Mouse &mouse)
{
	isHovered_ = this->contains(mouse.x(), mouse.y());
}

void ImageButton::render() const
{
	image_.render(x_, y_, scale_, al_map_rgba(delta_, delta_, delta_, 255));

	FontData::instance().renderText(
		x_ + width_ * 0.5f, y_ + height_ * 0.5f,
		text_,
		textSize_,
		textColor_,
		ALLEGRO_ALIGN_CENTER,
		FontData::TextFlags::CenterVertically);
}

bool ImageButton::isHovered() const
{
	return isHovered_;
}