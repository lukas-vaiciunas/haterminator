#include "Particle.h"

#include <allegro5/allegro_primitives.h>
#include "Camera.h"

Particle::Particle(
	float x, float y,
	float velX, float velY,
	float accX, float accY,
	float width, float height,
	float scale,
	float lifeSecs,
	const ALLEGRO_COLOR &color)
	:
	x_(x),
	y_(y),
	velX_(velX),
	velY_(velY),
	accX_(accX),
	accY_(accY),
	width_(width),
	height_(height),
	scale_(scale),
	lifeSecs_(lifeSecs),
	color_(color),
	lifeClock_(lifeSecs),
	dScale_(-scale / lifeClock_.target()),
	isLive_(true)
{}

void Particle::updateOnTick()
{
	x_ += velX_;
	y_ += velY_;

	velX_ += accX_;
	velY_ += accY_;

	scale_ += dScale_;
	if (scale_ < 0.0f)
		scale_ = 0.0f;

	lifeClock_.updateOnTick();

	if (lifeClock_.isDone())
		isLive_ = false;
}

void Particle::render(const Camera &camera) const
{
	float dX = x_ - camera.x();
	float dY = y_ - camera.y();

	al_draw_filled_rectangle(
		dX, dY,
		dX + width_ * scale_, dY + height_ * scale_,
		color_);
}

bool Particle::isLive() const
{
	return isLive_;
}