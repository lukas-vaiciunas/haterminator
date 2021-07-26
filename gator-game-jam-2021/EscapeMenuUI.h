#pragma once

class Keyboard;

#include "Boundable.h"
#include "Button.h"
#include "Key.h"

class EscapeMenuUI : public Boundable
{
private:
	Button closeButton_;
	Button menuButton_;
	bool isActive_;
public:
	EscapeMenuUI(const AABB &bounds);

	void updateOnTick();
	void updateOnMouseAxes(const Mouse &mouse);
	void updateOnMousePress(const Mouse &mouse);
	void updateOnKeyPress(const Keyboard &keyboard);

	void render() const;
};