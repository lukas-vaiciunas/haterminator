#include "Bullet.h"
#include "Camera.h"

Bullet::Bullet(
	float x, float y,
	float velX, float velY,
	float damage,
	const Image &image,
	float scale,
	float angleRad,
	float dAngleRad,
	float lifeSecs,
	bool isFromPlayer)
	:
	Entity(x, y, image, scale),
	velX_(velX),
	velY_(velY),
	damage_(damage),
	angleRad_(angleRad),
	dAngleRad_(dAngleRad),
	lifeSecs_(lifeSecs),
	lifeClock_(lifeSecs),
	isFromPlayer_(isFromPlayer),
	isLive_(true)
{}

void Bullet::kill()
{
	isLive_ = false;
}

void Bullet::updateOnTick()
{
	lifeClock_.updateOnTick();
	if (lifeClock_.isDone())
		isLive_ = false;

	x_ += velX_;
	y_ += velY_;
	angleRad_ += dAngleRad_;
}

void Bullet::render(const Camera &camera) const
{
	image_.render(x_ - camera.x(), y_ - camera.y(), scale_, angleRad_);
}

float Bullet::damage() const
{
	return damage_;
}

bool Bullet::isFromPlayer() const
{
	return isFromPlayer_;
}

bool Bullet::isLive() const
{
	return isLive_;
}