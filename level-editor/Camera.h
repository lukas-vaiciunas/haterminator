#pragma once

class Keyboard;

class Camera
{
private:
	float x_;
	float y_;
	float speed_;
public:
	Camera(float x, float y, float speed);

	void updateOnTick(const Keyboard &keyboard);

	float x() const;
	float y() const;
};