#include "BulletPool.h"

BulletPool::BulletPool(unsigned int size) :
	Pool(size)
{}

void BulletPool::updateOnTick()
{
	for (unsigned int i = 0; i < numLive_; )
	{
		Bullet *bullet = objects_.at(i);

		bullet->updateOnTick();

		if (!bullet->isLive())
		{
			this->removeAt_(i);
		}
		else
		{
			i++;
		}
	}
}

void BulletPool::render(const Camera &camera) const
{
	for (auto it = this->cbegin(); it != this->cend(); it++)
		(*it)->render(camera);
}