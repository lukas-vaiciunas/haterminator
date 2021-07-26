#include "Keyboard.h"

#include <allegro5/keycodes.h>

Keyboard::Keyboard()
{
	this->releaseAll_();
}

void Keyboard::updateOnPress(const ALLEGRO_EVENT &ev)
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_W:
		keys_[Key::W] = true;
		break;
	case ALLEGRO_KEY_A:
		keys_[Key::A] = true;
		break;
	case ALLEGRO_KEY_S:
		keys_[Key::S] = true;
		break;
	case ALLEGRO_KEY_D:
		keys_[Key::D] = true;
		break;
	case ALLEGRO_KEY_SPACE:
		keys_[Key::Space] = true;
		break;
	case ALLEGRO_KEY_ESCAPE:
		keys_[Key::Escape] = true;
		break;
	}
}

void Keyboard::updateOnRelease(const ALLEGRO_EVENT &ev)
{
	switch (ev.keyboard.keycode)
	{
	case ALLEGRO_KEY_W:
		keys_[Key::W] = false;
		break;
	case ALLEGRO_KEY_A:
		keys_[Key::A] = false;
		break;
	case ALLEGRO_KEY_S:
		keys_[Key::S] = false;
		break;
	case ALLEGRO_KEY_D:
		keys_[Key::D] = false;
		break;
	case ALLEGRO_KEY_SPACE:
		keys_[Key::Space] = false;
		break;
	case ALLEGRO_KEY_ESCAPE:
		keys_[Key::Escape] = false;
		break;
	}
}

void Keyboard::release(Key key)
{
	keys_[key] = false;
}

bool Keyboard::isPressed(Key key) const
{
	return keys_[key];
}

void Keyboard::releaseAll_()
{
	for (unsigned int i = 0; i < NUM_KEYS; i++)
		keys_[i] = false;
}