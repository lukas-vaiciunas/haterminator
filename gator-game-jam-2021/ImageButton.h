#pragma once

class Mouse;

#include <allegro5/allegro_color.h>
#include "Boundable.h"
#include "Image.h"

class ImageButton : public Boundable
{
private:
	const ALLEGRO_COLOR textColor_;
	const char *text_;
	unsigned char textSize_;

	Image image_;
	float scale_;

	unsigned char delta_;
	bool isHovered_;
public:
	ImageButton(
		float x, float y,
		const char *text,
		const ALLEGRO_COLOR &textColor,
		unsigned char textSize,
		const Image &image,
		float scale);

	void updateOnTick();
	void updateOnMouseAxes(const Mouse &mouse);

	void render() const;

	bool isHovered() const;
};