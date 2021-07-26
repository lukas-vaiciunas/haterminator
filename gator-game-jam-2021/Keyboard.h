#pragma once

#include <allegro5/events.h>
#include "Key.h"

class Keyboard
{
private:
	static constexpr uint8_t NUM_KEYS = 6;

	bool keys_[NUM_KEYS];

	void releaseAll_();
public:
	Keyboard();

	void updateOnPress(const ALLEGRO_EVENT &ev);
	void updateOnRelease(const ALLEGRO_EVENT &ev);

	void release(Key key);

	bool isPressed(Key key) const;
};