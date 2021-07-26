#include "Button.h"

#include <allegro5/allegro_primitives.h>
#include "Mouse.h"
#include "FontData.h"

Button::Button(
	const AABB &bounds,
	const char *text,
	unsigned char textSize,
	const ALLEGRO_COLOR &textColor,
	const ALLEGRO_COLOR &color,
	const ALLEGRO_COLOR &hoveredColor)
	:
	Boundable(bounds),
	text_(text),
	textSize_(textSize),
	textColor_(textColor),
	color_(color),
	hoveredColor_(hoveredColor),
	currentColor_(color),
	isHovered_(false)
{}

void Button::updateOnTick()
{
	if (isHovered_)
	{
		currentColor_.r += (hoveredColor_.r - currentColor_.r) * 0.1f;
		currentColor_.g += (hoveredColor_.g - currentColor_.g) * 0.1f;
		currentColor_.b += (hoveredColor_.b - currentColor_.b) * 0.1f;
	}
	else
	{
		currentColor_.r += (color_.r - currentColor_.r) * 0.1f;
		currentColor_.g += (color_.g - currentColor_.g) * 0.1f;
		currentColor_.b += (color_.b - currentColor_.b) * 0.1f;
	}
}

void Button::updateOnMouseAxes(const Mouse &mouse)
{
	isHovered_ = this->contains(mouse.x(), mouse.y());
}

void Button::render() const
{
	al_draw_filled_rectangle(x_, y_, x_ + width_, y_ + height_, currentColor_);

	FontData::instance().renderText(
		x_ + width_ * 0.5f, y_ + height_ * 0.5f,
		text_,
		textSize_,
		textColor_,
		ALLEGRO_ALIGN_CENTER,
		FontData::TextFlags::CenterVertically);
}

void Button::swapColors()
{
	const ALLEGRO_COLOR temp = hoveredColor_;

	hoveredColor_ = color_;
	color_ = temp;
}

bool Button::isHovered() const
{
	return isHovered_;
}