#include "ParticlePool.h"

ParticlePool::ParticlePool() :
	Pool(NUM_PARTICLES)
{}

ParticlePool &ParticlePool::instance()
{
	static ParticlePool particlePool;
	return particlePool;
}

void ParticlePool::updateOnTick()
{
	for (unsigned int i = 0; i < numLive_; )
	{
		Particle *particle = objects_.at(i);

		particle->updateOnTick();

		if (!particle->isLive())
		{
			this->removeAt_(i);
		}
		else
		{
			i++;
		}
	}
}

void ParticlePool::render(const Camera &camera) const
{
	for (auto it = this->cbegin(); it != this->cend(); it++)
		(*it)->render(camera);
}