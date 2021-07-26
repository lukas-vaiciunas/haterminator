#include "FillBar.h"

#include <allegro5/allegro_primitives.h>

FillBar::FillBar(
	const ALLEGRO_COLOR &backColor,
	const ALLEGRO_COLOR &frontColor,
	const ALLEGRO_COLOR &lagColor,
	const ALLEGRO_COLOR &outlineColor)
	:
	backColor_(backColor),
	frontColor_(frontColor),
	lagColor_(lagColor),
	outlineColor_(outlineColor),
	fillRatio_(1.0f),
	lagRatio_(0.0f)
{}

void FillBar::render(float x, float y, float width, float height) const
{
	float fillWidth = width * fillRatio_;
	float lagWidth = width * lagRatio_;

	al_draw_filled_rectangle(x, y, x + width, y + height, backColor_);
	al_draw_filled_rectangle(x, y, x + fillWidth, y + height, frontColor_);
	al_draw_filled_rectangle(x + fillWidth, y, x + fillWidth + lagWidth, y + height, lagColor_);
	al_draw_rectangle(x, y, x + width, y + height, outlineColor_, 1.0f);
}