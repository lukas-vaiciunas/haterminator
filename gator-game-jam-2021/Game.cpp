#include "Game.h"
#include "Tile.h"
#include "Config.h"

Game::Game(const CharacterAnimations &animations) :
	level_("data/maps/level-1.dat", animations, 25),
	statusUI_(AABB(0.0f, 0.0f, 320.0f, 64.0f)),
	escapeMenuUI_(
		AABB(
			Config::displayWidth * 0.5f - 128.0f,
			Config::displayHeight * 0.5f - 128.0f,
			256.0f,
			256.0f))
{}

void Game::updateOnTick(const Keyboard &keyboard, const Mouse &mouse)
{
	level_.updateOnTick(keyboard, mouse);
	statusUI_.updateOnTick(level_.player());
	escapeMenuUI_.updateOnTick();
}

void Game::updateOnMouseAxes(const Mouse &mouse)
{
	escapeMenuUI_.updateOnMouseAxes(mouse);
}

void Game::updateOnMousePress(const Mouse &mouse)
{
	escapeMenuUI_.updateOnMousePress(mouse);
}

void Game::updateOnKeyPress(const Keyboard &keyboard)
{
	level_.updateOnKeyPress(keyboard);
	escapeMenuUI_.updateOnKeyPress(keyboard);
}

void Game::render() const
{
	level_.render();
	statusUI_.render();
	escapeMenuUI_.render();
}