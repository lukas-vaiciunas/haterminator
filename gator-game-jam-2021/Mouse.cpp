#include "Mouse.h"

Mouse::Mouse() :
	x_(0),
	y_(0)
{
	this->releaseAll_();
}

void Mouse::updateOnAxes(const ALLEGRO_EVENT &ev)
{
	x_ = ev.mouse.x;
	y_ = ev.mouse.y;
}

void Mouse::updateOnPress(const ALLEGRO_EVENT &ev)
{
	if (ev.mouse.button & 1)
		buttons_[Button::M1] = true;
}

void Mouse::updateOnRelease(const ALLEGRO_EVENT &ev)
{
	if (ev.mouse.button & 1)
		buttons_[Button::M1] = false;
}

void Mouse::release(Button button)
{
	buttons_[button] = false;
}

bool Mouse::isPressed(Button button) const
{
	return buttons_[button];
}

int Mouse::x() const
{
	return x_;
}

int Mouse::y() const
{
	return y_;
}

void Mouse::releaseAll_()
{
	for (unsigned int i = 0; i < NUM_BUTTONS; i++)
		buttons_[i] = false;
}