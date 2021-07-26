#pragma once

#include "Pool.h"
#include "Particle.h"

class ParticlePool : public Pool<Particle>
{
private:
	static constexpr unsigned int NUM_PARTICLES = 100;

	ParticlePool();
	~ParticlePool() {}
public:
	ParticlePool(const ParticlePool &) = delete;
	ParticlePool &operator=(const ParticlePool &) = delete;

	static ParticlePool &instance();

	void updateOnTick();

	void render(const Camera &camera) const;
};