#pragma once

class Painter;

class StatusUI
{
private:
	float x_;
	float y_;
public:
	StatusUI(float x, float y);

	void render(const Painter &painter) const;
};