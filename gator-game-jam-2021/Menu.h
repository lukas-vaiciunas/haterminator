#pragma once

class Mouse;

#include "Button.h"

class Menu
{
private:
	Button playButton_;
	Button quitButton_;
public:
	Menu();

	void updateOnTick();
	void updateOnMouseAxes(const Mouse &mouse);
	void updateOnMousePress(const Mouse &mouse);

	void render() const;
};