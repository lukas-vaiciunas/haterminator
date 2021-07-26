#include "StatusUI.h"

#include <allegro5/allegro_primitives.h>
#include "Player.h"
#include "FontData.h"

StatusUI::StatusUI(const AABB &bounds) :
	Boundable(bounds),
	healthBar_(
		al_map_rgb(25, 25, 25),
		al_map_rgb(125, 0, 0),
		al_map_rgb(225, 225, 225),
		al_map_rgb(225, 225, 225))
{}

void StatusUI::updateOnTick(const Player &player)
{
	healthBar_.update(player.maxHealth(), player.health());
}

void StatusUI::render() const
{
	al_draw_filled_rectangle(x_, y_, x_ + width_, y_ + height_, al_map_rgba(25, 25, 25, 125));
	
	FontData::instance().renderText(
		x_ + width_ * 0.5f, y_,
		"Health",
		16,
		al_map_rgb(225, 225, 225),
		ALLEGRO_ALIGN_CENTER);
	
	healthBar_.render(x_ + 16.0f, y_ + 16.0f, x_ + width_ - 32.0f, y_ + height_ - 32.0f);
}