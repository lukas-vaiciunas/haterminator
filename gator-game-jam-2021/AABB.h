#pragma once

class AABB
{
protected:
	float x_;
	float y_;
	float width_;
	float height_;
public:
	AABB(float x, float y, float width, float height);
	virtual ~AABB() {}

	float distanceTo(const AABB &other) const;
	float angleRadTo(const AABB &other) const;
	bool isCollidingWith(const AABB &other) const;
	bool contains(float x, float y) const;

	float x() const;
	float y() const;
	float width() const;
	float height() const;
};