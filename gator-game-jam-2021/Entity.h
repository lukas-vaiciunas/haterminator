#pragma once

class Camera;

#include "Boundable.h"
#include "Image.h"

class Entity : public Boundable
{
protected:
	Image image_;
	float scale_;
public:
	Entity(float x, float y, const Image &image, float scale);
	virtual ~Entity() {}

	virtual void render(const Camera &camera) const;
};