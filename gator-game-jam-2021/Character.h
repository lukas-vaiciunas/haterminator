#pragma once

class Camera;
class ParticlePool;

#include "Boundable.h"
#include "TickClock.h"
#include "CharacterAnimations.h"

class Character : public Boundable
{
protected:
	CharacterAnimations animations_;
	TickClock fireClock_;
	float health_;
	float maxHealth_;
	float velX_;
	float velY_;
	float speed_;
	float scale_;
	bool isLive_;

	void fixVelocity_();
	void selectAnimation_();
	void hurt_(float damage);
	virtual void onDeath_();
public:
	Character(
		float x, float y,
		float health,
		float speed,
		float fireDelaySecs,
		const char *animationSheetPath,
		float scale);

	Character(
		float x, float y,
		float health,
		float speed,
		float fireDelaySecs,
		const CharacterAnimations &animations,
		float scale);

	virtual ~Character() {}

	virtual void render(const Camera &camera) const;

	float health() const;
	float maxHealth() const;
	bool isLive() const;
};