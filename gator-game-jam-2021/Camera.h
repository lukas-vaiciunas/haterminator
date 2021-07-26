#pragma once

class AABB;

class Camera
{
private:
	float x_;
	float y_;
public:
	Camera(float x, float y);

	void centerOn(const AABB &aabb);

	float x() const;
	float y() const;
};