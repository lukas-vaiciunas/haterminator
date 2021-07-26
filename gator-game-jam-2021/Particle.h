#pragma once

class Camera;

#include <allegro5/allegro_color.h>
#include "TickClock.h"

class Particle
{
private:
	const ALLEGRO_COLOR color_;
	TickClock lifeClock_;
	float x_;
	float y_;
	float velX_;
	float velY_;
	float accX_;
	float accY_;
	float width_;
	float height_;
	float scale_;
	float dScale_;
	float lifeSecs_;
	bool isLive_;
public:
	Particle(
		float x, float y,
		float velX, float velY,
		float accX, float accY,
		float width, float height,
		float scale,
		float lifeSecs,
		const ALLEGRO_COLOR &color);

	void updateOnTick();

	void render(const Camera &camera) const;

	bool isLive() const;
};