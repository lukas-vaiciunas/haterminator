#include "Camera.h"
#include "Keyboard.h"

Camera::Camera(float x, float y, float speed) :
	x_(x),
	y_(y),
	speed_(speed)
{}

void Camera::updateOnTick(const Keyboard &keyboard)
{
	if (keyboard.isPressed(Key::W))
		y_ -= speed_;

	if (keyboard.isPressed(Key::A))
		x_ -= speed_;

	if (keyboard.isPressed(Key::S))
		y_ += speed_;

	if (keyboard.isPressed(Key::D))
		x_ += speed_;
}

float Camera::x() const
{
	return x_;
}

float Camera::y() const
{
	return y_;
}