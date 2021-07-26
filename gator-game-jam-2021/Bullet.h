#pragma once

#include "Entity.h"
#include "TickClock.h"

class Bullet : public Entity
{
private:
	TickClock lifeClock_;
	float velX_;
	float velY_;
	float damage_;
	float angleRad_;
	float dAngleRad_;
	float lifeSecs_;
	bool isFromPlayer_;
	bool isLive_;
public:
	Bullet(
		float x, float y,
		float velX, float velY,
		float damage,
		const Image &image,
		float scale,
		float angleRad,
		float dAngleRad,
		float lifeSecs,
		bool isFromPlayer);

	void kill();

	void updateOnTick();

	void render(const Camera &camera) const override;

	float damage() const;
	bool isFromPlayer() const;
	bool isLive() const;
};