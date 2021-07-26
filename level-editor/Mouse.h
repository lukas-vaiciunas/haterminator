#pragma once

#include <allegro5/events.h>

class Mouse
{
private:
	static constexpr uint8_t NUM_BUTTONS = 1;

	bool buttons_[NUM_BUTTONS];
	int x_;
	int y_;

	void releaseAll_();
public:
	enum Button
	{
		M1
	};

	Mouse();

	void updateOnAxes(const ALLEGRO_EVENT &ev);
	void updateOnPress(const ALLEGRO_EVENT &ev);
	void updateOnRelease(const ALLEGRO_EVENT &ev);

	void release(Button button);

	bool isPressed(Button button) const;
	int x() const;
	int y() const;
};