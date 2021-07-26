#pragma once

class Keyboard;

#include "Camera.h"
#include "Level.h"
#include "Painter.h"
#include "ImagesUI.h"
#include "StatusUI.h"

class Driver
{
private:
	Camera camera_;
	Level level_;
	Painter painter_;
	ImagesUI imagesUI_;
	StatusUI statusUI_;
public:
	Driver();

	void updateOnTick(const Keyboard &keyboard);
	void updateOnKeyPress(const Keyboard &keyboard);
	void updateOnMousePress(const Mouse &mouse);

	void render(const Mouse &mouse) const;
};