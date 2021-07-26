#pragma once

#include <allegro5/allegro_color.h>

class FillBar
{
private:
	const ALLEGRO_COLOR backColor_;
	const ALLEGRO_COLOR frontColor_;
	const ALLEGRO_COLOR lagColor_;
	const ALLEGRO_COLOR outlineColor_;

	float fillRatio_;
	float lagRatio_;
public:
	FillBar(
		const ALLEGRO_COLOR &backColor,
		const ALLEGRO_COLOR &frontColor,
		const ALLEGRO_COLOR &lagColor,
		const ALLEGRO_COLOR &outlineColor);

	template<typename T>
	void update(const T &maxValue, const T &fillValue);

	void render(float x, float y, float width, float height) const;
};

template<typename T>
void FillBar::update(const T &maxValue, const T &fillValue)
{
	float oldFillRatio = fillRatio_;
	fillRatio_ = fillValue / maxValue;
	lagRatio_ += oldFillRatio - fillRatio_;

	lagRatio_ *= 0.90f;
	if (lagRatio_ < 0.01f)
		lagRatio_ = 0.0f;
}