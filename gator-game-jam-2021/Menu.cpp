#include "Menu.h"
#include "EventQueue.h"
#include "Event.h"
#include "Mouse.h"
#include "Config.h"
#include "FontData.h"

Menu::Menu() :
	playButton_(
		AABB(
			Config::displayWidth * 0.5f - 64.0f,
			Config::displayHeight * 0.5f - 16.0f,
			128.0f,
			32.0f
		),
		"Play",
		32,
		al_map_rgb(255, 69, 103),
		al_map_rgb(25, 25, 25),
		al_map_rgb(225, 225, 225)),
	quitButton_(
		AABB(
			Config::displayWidth * 0.5f - 64.0f,
			Config::displayHeight * 0.75f - 16.0f,
			128.0f,
			32.0f
		),
		"Quit",
		32,
		al_map_rgb(255, 69, 103),
		al_map_rgb(25, 25, 25),
		al_map_rgb(225, 225, 225))
{}

void Menu::updateOnTick()
{
	playButton_.updateOnTick();
	quitButton_.updateOnTick();
}

void Menu::updateOnMouseAxes(const Mouse &mouse)
{
	playButton_.updateOnMouseAxes(mouse);
	quitButton_.updateOnMouseAxes(mouse);
}

void Menu::updateOnMousePress(const Mouse &mouse)
{
	if (mouse.isPressed(Mouse::Button::M1))
	{
		if (playButton_.isHovered())
		{
			EventQueue::instance().send(new EventChangeDriverState(DriverState::CharacterSelect));
		}
		else if (quitButton_.isHovered())
		{
			EventQueue::instance().send(new EventChangeDriverState(DriverState::Quit));
		}
	}
}

void Menu::render() const
{
	FontData::instance().renderText(
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.25f,
		"Haterminator",
		128,
		al_map_rgb(225, 225, 225),
		ALLEGRO_ALIGN_CENTER,
		FontData::TextFlags::CenterVertically);

	FontData::instance().renderText(
		0.0f,
		Config::displayHeight - 32.0f,
		"Lukas Vaiciunas",
		32,
		al_map_rgb(225, 225, 225),
		ALLEGRO_ALIGN_LEFT,
		FontData::TextFlags::None);
	
	playButton_.render();
	quitButton_.render();
}