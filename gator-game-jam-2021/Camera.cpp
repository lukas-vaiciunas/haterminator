#include "Camera.h"
#include "AABB.h"
#include "Config.h"

Camera::Camera(float x, float y) :
	x_(x),
	y_(y)
{}

void Camera::centerOn(const AABB &aabb)
{
	x_ = aabb.x() + (aabb.width() - Config::displayWidth) * 0.5f;
	y_ = aabb.y() + (aabb.height() - Config::displayHeight) * 0.5f;
}

float Camera::x() const
{
	return x_;
}

float Camera::y() const
{
	return y_;
}