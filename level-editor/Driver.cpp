#include "Driver.h"
#include "Keyboard.h"

Driver::Driver() :
	camera_(0.0f, 0.0f, 4.0f),
	level_("data/maps/level-1.dat", "data/maps/map-1.dat", 20, 20),
	painter_(),
	imagesUI_(Key::T, "img/tilesheet.png"),
	statusUI_(0.0f, 0.0f)
{}

void Driver::updateOnTick(const Keyboard &keyboard)
{
	camera_.updateOnTick(keyboard);
}

void Driver::updateOnKeyPress(const Keyboard &keyboard)
{
	imagesUI_.updateOnKeyPress(keyboard);

	if (keyboard.isPressed(Key::NUM_0))
	{
		painter_.setImageId(0);
	}
	else if (keyboard.isPressed(Key::C))
	{
		painter_.setIsCollidable(!painter_.isCollidable());
	}
	else if (keyboard.isPressed(Key::P))
	{
		painter_.setIsPlacingSpawn(!painter_.isPlacingSpawn());
	}
	else if (keyboard.isPressed(Key::F))
	{
		level_.save();
	}
}

void Driver::updateOnMousePress(const Mouse &mouse)
{
	if (imagesUI_.isActive())
	{
		imagesUI_.updateOnMousePress(mouse, painter_);
	}
	else
	{
		painter_.updateOnMousePress(mouse, level_, camera_);
	}
}

void Driver::render(const Mouse &mouse) const
{
	level_.render(camera_);

	if (imagesUI_.isActive())
	{
		imagesUI_.render(mouse);
	}
	else
	{
		painter_.render(mouse, level_, camera_);
		statusUI_.render(painter_);
	}
}