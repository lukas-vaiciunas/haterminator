#include "Player.h"

#include <cmath>
#include "Camera.h"
#include "Keyboard.h"
#include "Mouse.h"
#include "BulletPool.h"
#include "Tile.h"
#include "Map.h"
#include "EventQueue.h"
#include "Event.h"

Player::Player(
	float x, float y,
	float health,
	float speed,
	float fireDelaySecs,
	const char *animationSheetPath,
	float scale)
	:
	Character(x, y, health, speed, fireDelaySecs, animationSheetPath, scale)
{}

Player::Player(
	float x, float y,
	float health,
	float speed,
	float fireDelaySecs,
	const CharacterAnimations &animations,
	float scale)
	:
	Character(x, y, health, speed, fireDelaySecs, animations, scale)
{}

void Player::updateOnTick(
	const Keyboard &keyboard,
	const Mouse &mouse,
	const Map &map,
	const Camera &camera,
	BulletPool &bulletPool)
{
	if (!isLive_)
		return;

	animations_.updateOnTick();
	fireClock_.updateOnTick();

	for (auto it = bulletPool.cbegin(); it != bulletPool.cend(); it++)
	{
		if (!(*it)->isFromPlayer() && this->isCollidingWith(**it))
		{
			(*it)->kill();
			this->hurt_((*it)->damage());

			if (!isLive_)
			{
				EventQueue::instance().send(new EventLoss());
			}
		}
	}

	if (mouse.isPressed(Mouse::Button::M1) && fireClock_.isDone())
	{
		float cX = x_ + width_ * 0.5f;
		float cY = y_ + height_ * 0.5f;

		float mouseRealX = mouse.x() + camera.x();
		float mouseRealY = mouse.y() + camera.y();

		float dX = mouseRealX - cX - 8;
		float dY = mouseRealY - cY - 8;

		float speed = 7.0f;
		float angleRad = atan2f(dY, dX);

		fireClock_.reset();
		bulletPool.add(
			new Bullet(
				cX, cY,
				speed * cosf(angleRad), speed * sinf(angleRad),
				10.0f,
				Image(16, 16, al_map_rgb(255, 255, 0)),
				1.0f,
				angleRad,
				0.0f,
				4.0f,
				true));
	}	

	float oldX = x_;
	float oldY = y_;

	x_ += velX_;
	y_ += velY_;

	if (keyboard.isPressed(Key::W))
	{
		velY_ = -speed_;
	}
	else if (keyboard.isPressed(Key::S))
	{
		velY_ = speed_;
	}
	else
	{
		velY_ = 0.0f;
	}

	if (keyboard.isPressed(Key::A))
	{
		velX_ = -speed_;
	}
	else if (keyboard.isPressed(Key::D))
	{
		velX_ = speed_;
	}
	else
	{
		velX_ = 0.0f;
	}

	const std::vector<Tile *> &collidingTiles = map.getCollidableTilesTouching(*this);

	float oldRight = oldX + width_;
	float newRight = x_ + width_;

	float oldBottom = oldY + height_;
	float newBottom = y_ + height_;

	for (Tile *tile : collidingTiles)
	{
		float tileRight = tile->x() + tile->width();
		float tileBottom = tile->y() + tile->height();

		if (oldRight <= tile->x() && newRight > tile->x())
		{
			x_ = tile->x() - width_;
		}
		else if (oldX >= tileRight && x_ < tileRight)
		{
			x_ = tileRight;
		}
		
		if (oldBottom <= tile->y() && newBottom > tile->y())
		{
			y_ = tile->y() - height_;
		}
		else if (oldY >= tileBottom && y_ < tileBottom)
		{
			y_ = tileBottom;
		}
	}

	this->fixVelocity_();
	this->selectAnimation_();
}