#pragma once

class Menu;
class CharacterSelect;
class Game;
class Mouse;
class Keyboard;

#include <allegro5/events.h>
#include "Listener.h"
#include "EventQueue.h"
#include "Mouse.h"
#include "Keyboard.h"
#include "DriverState.h"
#include "CharacterAnimations.h"

class Driver : public Listener
{
private:
	EventQueue &eventQueue_;
	Menu *menu_;
	CharacterSelect *characterSelect_;
	Game *game_;
	CharacterAnimations animations_;
	Mouse mouse_;
	Keyboard keyboard_;
	DriverState state_;

	bool isDone_;

	void changeState_(DriverState toState);
public:
	Driver();
	~Driver();

	void onEvent(const Event &ev) override;

	void updateOnTick();
	void updateOnMouseAxes(ALLEGRO_EVENT &ev);
	void updateOnMousePress(ALLEGRO_EVENT &ev);
	void updateOnMouseRelease(ALLEGRO_EVENT &ev);
	void updateOnKeyPress(ALLEGRO_EVENT &ev);
	void updateOnKeyRelease(ALLEGRO_EVENT &ev);
	void updateOnDisplayClose();

	void render() const;

	bool isDone() const;
};