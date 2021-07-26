#include "Painter.h"

#include <allegro5/allegro_primitives.h>
#include "Mouse.h"
#include "Level.h"
#include "Camera.h"
#include "Constants.h"

Painter::Painter() :
	imageId_(0),
	isCollidable_(false)
{}

void Painter::updateOnMousePress(const Mouse &mouse, Level &level, const Camera &camera)
{
	if (mouse.isPressed(Mouse::Button::M1))
	{
		Map &map = level.map();

		float mapMouseX = mouse.x() + camera.x();
		float mapMouseY = mouse.y() + camera.y();

		unsigned int col = map.calcCol(mapMouseX);
		unsigned int row = map.calcRow(mapMouseY);

		if (map.isInBounds(col, row))
		{
			if (isPlacingSpawn_)
			{
				level.setPlayerSpawn(col, row);
			}
			else
			{
				level.map().put(col, row, imageId_, isCollidable_);
			}
		}
	}
}

void Painter::render(const Mouse &mouse, const Level &level, const Camera &camera) const
{
	const Map &map = level.map();

	float mapMouseX = mouse.x() + camera.x();
	float mapMouseY = mouse.y() + camera.y();

	unsigned int col = map.calcCol(mapMouseX);
	unsigned int row = map.calcRow(mapMouseY);

	if (map.isInBounds(col, row))
	{
		float trueTileSize = Constants::tileSize * Constants::tileScale;

		float dX = col * trueTileSize - camera.x();
		float dY = row * trueTileSize - camera.y();

		al_draw_rectangle(dX, dY, dX + trueTileSize, dY + trueTileSize, al_map_rgb(255, 0, 255), 2.0f);
	}
}

void Painter::setImageId(unsigned int imageId)
{
	imageId_ = imageId;
}

void Painter::setIsCollidable(bool isCollidable)
{
	isCollidable_ = isCollidable;
}

void Painter::setIsPlacingSpawn(bool isPlacingSpawn)
{
	isPlacingSpawn_ = isPlacingSpawn;
}

unsigned int Painter::imageId() const
{
	return imageId_;
}

bool Painter::isCollidable() const
{
	return isCollidable_;
}

bool Painter::isPlacingSpawn() const
{
	return isPlacingSpawn_;
}