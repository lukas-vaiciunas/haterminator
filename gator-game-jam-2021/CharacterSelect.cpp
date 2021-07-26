#include "CharacterSelect.h"
#include "FontData.h"
#include "Mouse.h"
#include "EventQueue.h"
#include "Event.h"
#include "Constants.h"
#include "Config.h"

CharacterSelect::CharacterSelect() :
	playButton_(
		Button(
			AABB(
				Config::displayWidth * 0.5f - 64.0f,
				Config::displayHeight * 0.75f - 16.0f,
				128.0f,
				32.0f
			),
			"Play",
			32,
			al_map_rgb(255, 69, 103),
			al_map_rgb(25, 25, 25),
			al_map_rgb(225, 225, 225)))
{
	ALLEGRO_BITMAP *player1sheet = al_load_bitmap("img/player-1.png");
	animations_.push_back(CharacterAnimations(player1sheet, 0.2f));
	al_destroy_bitmap(player1sheet);
	player1sheet = nullptr;

	ALLEGRO_BITMAP *player2sheet = al_load_bitmap("img/player-2.png");
	animations_.push_back(CharacterAnimations(player2sheet, 0.2f));
	al_destroy_bitmap(player2sheet);
	player2sheet = nullptr;

	/*ALLEGRO_BITMAP *player2sheet = al_load_bitmap("img/player-2-animation-sheet.png");
	animations_.push_back(CharacterAnimations(player2sheet, 0.2f));
	al_destroy_bitmap(player2sheet);
	player2sheet = nullptr;*/

	buttons_.push_back(
		Button(
			AABB(
				Config::displayWidth * 0.25f - 64.0f,
				Config::displayHeight * 0.5f - 16.0f,
				128.0f,
				32.0f
			),
			"Tux",
			32,
			al_map_rgb(255, 69, 103),
			al_map_rgb(25, 25, 25),
			al_map_rgb(225, 225, 225)));

	buttons_.push_back(
		Button(
			AABB(
				Config::displayWidth * 0.25f - 64.0f + 128.0f + 32.0f,
				Config::displayHeight * 0.5f - 16.0f,
				128.0f,
				32.0f
			),
			"Red",
			32,
			al_map_rgb(255, 69, 103),
			al_map_rgb(25, 25, 25),
			al_map_rgb(225, 225, 225)));

	selectedIndex_ = 0;

	buttons_.at(selectedIndex_).swapColors();
}

void CharacterSelect::updateOnTick()
{
	playButton_.updateOnTick();

	for (size_t i = 0; i < animations_.size(); i++)
	{
		animations_.at(i).updateOnTick();
		buttons_.at(i).updateOnTick();
	}
}

void CharacterSelect::updateOnMouseAxes(const Mouse &mouse)
{
	playButton_.updateOnMouseAxes(mouse);

	for (auto it = buttons_.begin(); it != buttons_.end(); it++)
		it->updateOnMouseAxes(mouse);
}

void CharacterSelect::updateOnMousePress(const Mouse &mouse)
{
	if (mouse.isPressed(Mouse::Button::M1))
	{
		if (playButton_.isHovered())
		{
			EventQueue::instance().send(new EventChangePlayerAnimations(animations_.at(selectedIndex_)));
			EventQueue::instance().send(new EventChangeDriverState(DriverState::Play));
		}
		else
		{
			for (size_t i = 0; i < buttons_.size(); i++)
			{
				if (buttons_.at(i).isHovered())
				{
					buttons_.at(selectedIndex_).swapColors();
					selectedIndex_ = i;
					buttons_.at(selectedIndex_).swapColors();
				}
			}
		}
	}
}

void CharacterSelect::render() const
{
	float trueTileSize = Constants::tileSize * Constants::tileScale;

	FontData::instance().renderText(
		Config::displayWidth * 0.5f,
		Config::displayHeight * 0.25f,
		"Choose Your Character",
		128,
		al_map_rgb(225, 225, 225),
		ALLEGRO_ALIGN_CENTER,
		FontData::TextFlags::CenterVertically);

	playButton_.render();

	for (size_t i = 0; i < buttons_.size(); i++)
	{
		const Button &button = buttons_.at(i);

		button.render();
		animations_.at(i).currentFrame().render(
			button.x() + button.width() * 0.5f - trueTileSize * 0.5f,
			button.y() - trueTileSize,
			Constants::tileScale);
	}
}