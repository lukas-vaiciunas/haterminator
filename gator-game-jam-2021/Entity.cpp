#include "Entity.h"
#include "Camera.h"

Entity::Entity(float x, float y, const Image &image, float scale) :
	Boundable(AABB(x, y, image.width() * scale, image.height() * scale)),
	image_(image),
	scale_(scale)
{}

void Entity::render(const Camera &camera) const
{
	image_.render(x_ - camera.x(), y_ - camera.y(), scale_);
}