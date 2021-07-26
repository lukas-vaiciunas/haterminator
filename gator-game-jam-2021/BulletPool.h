#pragma once

#include "Pool.h"
#include "Bullet.h"

class BulletPool : public Pool<Bullet>
{
public:
	BulletPool(unsigned int size);

	void updateOnTick();

	void render(const Camera &camera) const;
};