#pragma once

class Mouse;

#include <allegro5/allegro_color.h>
#include "Boundable.h"

class Button : public Boundable
{
private:
	ALLEGRO_COLOR color_;
	ALLEGRO_COLOR hoveredColor_;
	const ALLEGRO_COLOR textColor_;
	ALLEGRO_COLOR currentColor_;
	const char *text_;
	unsigned char textSize_;
	bool isHovered_;
public:
	Button(
		const AABB &bounds,
		const char *text,
		unsigned char textSize,
		const ALLEGRO_COLOR &textColor,
		const ALLEGRO_COLOR &color,
		const ALLEGRO_COLOR &hoveredColor);

	void updateOnTick();
	void updateOnMouseAxes(const Mouse &mouse);

	void render() const;

	void swapColors();

	bool isHovered() const;
};