#include "StatusUI.h"

#include <string>
#include "FontData.h"
#include "Painter.h"

StatusUI::StatusUI(float x, float y) :
	x_(x),
	y_(y)
{}

void StatusUI::render(const Painter &painter) const
{
	const FontData &fontData = FontData::instance();
	unsigned char fontSize = 16;

	fontData.renderText(
		x_, y_,
		"Image ID: " + std::to_string(painter.imageId()),
		fontSize,
		al_map_rgb(255, 0, 255),
		ALLEGRO_ALIGN_LEFT);

	fontData.renderText(
		x_, y_ + fontSize,
		"Collidable: " + std::string((painter.isCollidable() ? "true" : "false")),
		fontSize,
		al_map_rgb(255, 0, 255),
		ALLEGRO_ALIGN_LEFT);

	fontData.renderText(
		x_, y_ + fontSize * 2.0f,
		"Placing Spawn: " + std::string((painter.isPlacingSpawn () ? "true" : "false")),
		fontSize,
		al_map_rgb(255, 0, 255),
		ALLEGRO_ALIGN_LEFT);
}