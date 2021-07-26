#include "AABB.h"

#include <cmath>

AABB::AABB(float x, float y, float width, float height) :
	x_(x),
	y_(y),
	width_(width),
	height_(height)
{}

float AABB::distanceTo(const AABB &other) const
{
	float cX = x_ + width_ * 0.5f;
	float cY = y_ + height_ * 0.5f;

	float otherCx = other.x_ + other.width_ * 0.5f;
	float otherCy = other.y_ + other.height_ * 0.5f;

	float dX = otherCx - cX;
	float dY = otherCy - cY;

	return sqrtf(powf(dX, 2.0f) + powf(dY, 2.0f));
}

float AABB::angleRadTo(const AABB &other) const
{
	float cX = x_ + width_ * 0.5f;
	float cY = y_ + height_ * 0.5f;

	float otherCx = other.x_ + other.width_ * 0.5f;
	float otherCy = other.y_ + other.height_ * 0.5f;

	float dX = otherCx - cX;
	float dY = otherCy - cY;

	return atan2f(dY, dX);
}

bool AABB::isCollidingWith(const AABB &other) const
{
	return (x_ < other.x_ + other.width_ &&
		x_ + width_ > other.x_ &&
		y_ < other.y_ + other.height_ &&
		y_ + height_ > other.y_);
}

bool AABB::contains(float x, float y) const
{
	return (x_ < x &&
		x_ + width_ > x &&
		y_ < y &&
		y_ + height_ > y);
}

float AABB::x() const
{
	return x_;
}

float AABB::y() const
{
	return y_;
}

float AABB::width() const
{
	return width_;
}

float AABB::height() const
{
	return height_;
}