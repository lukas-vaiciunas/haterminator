#include "EscapeMenuUI.h"

#include <allegro5/allegro_primitives.h>
#include "Mouse.h"
#include "Keyboard.h"
#include "EventQueue.h"
#include "Event.h"

EscapeMenuUI::EscapeMenuUI(const AABB &bounds) :
	Boundable(bounds),
	closeButton_(
		AABB(
			bounds.x() + 16.0f,
			bounds.y() + 16.0f,
			bounds.width() - 32.0f,
			32.0f),
		"Close",
		32,
		al_map_rgb(255, 69, 103),
		al_map_rgb(25, 25, 25),
		al_map_rgb(225, 225, 225)),
	menuButton_(
		AABB(
			bounds.x() + 16.0f,
			bounds.y() + 80.0f,
			bounds.width() - 32.0f,
			32.0f),
		"Menu",
		32,
		al_map_rgb(255, 69, 103),
		al_map_rgb(25, 25, 25),
		al_map_rgb(225, 225, 225)),
	isActive_(false)
{}

void EscapeMenuUI::updateOnTick()
{
	if (!isActive_)
		return;

	closeButton_.updateOnTick();
	menuButton_.updateOnTick();

}
void EscapeMenuUI::updateOnMouseAxes(const Mouse &mouse)
{
	if (!isActive_)
		return;

	closeButton_.updateOnMouseAxes(mouse);
	menuButton_.updateOnMouseAxes(mouse);
}

void EscapeMenuUI::updateOnMousePress(const Mouse &mouse)
{
	if (!isActive_)
		return;

	if (mouse.isPressed(Mouse::Button::M1))
	{
		if (closeButton_.isHovered())
		{
			isActive_ = false;
		}
		else if (menuButton_.isHovered())
		{
			EventQueue::instance().send(new EventChangeDriverState(DriverState::Menu));
		}
	}
}

void EscapeMenuUI::updateOnKeyPress(const Keyboard &keyboard)
{
	if (keyboard.isPressed(Key::Escape))
		isActive_ = !isActive_;
}

void EscapeMenuUI::render() const
{
	if (!isActive_)
		return;

	al_draw_filled_rectangle(x_, y_, x_ + width_, y_ + height_, al_map_rgba(25, 25, 25, 150));

	closeButton_.render();
	menuButton_.render();
}