#pragma once

class Camera;

#include "Boundable.h"

class Tile : public Boundable
{
private:
	unsigned int imageId_;
	float scale_;
	bool isCollidable_;
public:
	Tile(float x, float y, unsigned int imageId, float scale, bool isCollidable);

	Tile *clone(float x, float y) const;
	
	void render(const Camera &camera) const;

	bool isCollidable() const;
};