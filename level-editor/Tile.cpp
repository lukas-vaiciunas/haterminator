#include "Tile.h"
#include "Camera.h"
#include "ImageData.h"
#include "Image.h"

Tile::Tile(float x, float y, unsigned int imageId, float scale, bool isCollidable) :
	Boundable(
		AABB(
			x, y,
			ImageData::instance().get(imageId).width() * scale,
			ImageData::instance().get(imageId).height() * scale)),
	imageId_(imageId),
	scale_(scale),
	isCollidable_(isCollidable)
{}

Tile *Tile::clone(float x, float y) const
{
	return new Tile(x, y, imageId_, scale_, isCollidable_);
}

void Tile::render(const Camera &camera) const
{
	ImageData::instance().get(imageId_).render(x_ - camera.x(), y_ - camera.y(), scale_);
}

unsigned int Tile::imageId() const
{
	return imageId_;
}

bool Tile::isCollidable() const
{
	return isCollidable_;
}