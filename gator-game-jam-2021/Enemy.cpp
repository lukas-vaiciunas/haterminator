#include "Enemy.h"
#include "Player.h"
#include "Camera.h"
#include "Constants.h"
#include "BulletPool.h"
#include "Map.h"

Enemy::Enemy(
	float x, float y,
	float attackDistance,
	float orbitDistance,
	float retreatDistance,
	float attentionDistance,
	float health,
	float speed,
	float fireDelaySecs,
	const char *animationSheetPath,
	float scale)
	:
	Character(x, y, health, speed, fireDelaySecs, animationSheetPath, scale),
	target_(nullptr),
	healthBar_(
		al_map_rgb(25, 25, 25),
		al_map_rgb(125, 0, 0),
		al_map_rgb(225, 225, 225),
		al_map_rgb(225, 225, 225)),
	state_(State::Idle),
	attackDistance_(attackDistance),
	orbitDistance_(orbitDistance),
	retreatDistance_(retreatDistance),
	attentionDistance_(attentionDistance)
{}

Enemy::Enemy(
	float x, float y,
	float attackDistance,
	float orbitDistance,
	float retreatDistance,
	float attentionDistance,
	float health,
	float speed,
	float fireDelaySecs,
	const CharacterAnimations &animations,
	float scale)
	:
	Character(x, y, health, speed, fireDelaySecs, animations, scale),
	target_(nullptr),
	healthBar_(
		al_map_rgb(25, 25, 25),
		al_map_rgb(125, 0, 0),
		al_map_rgb(225, 225, 225),
		al_map_rgb(225, 225, 225)),
	state_(State::Idle),
	attackDistance_(attackDistance),
	orbitDistance_(orbitDistance),
	retreatDistance_(retreatDistance),
	attentionDistance_(attentionDistance)
{}

void Enemy::updateOnTick(const Player &player, const Map &map, BulletPool &bulletPool)
{
	healthBar_.update(maxHealth_, health_);
	animations_.updateOnTick();
	fireClock_.updateOnTick();

	if (target_)
	{
		if (!player.isLive())
		{
			target_ = nullptr;
			state_ = State::Idle;
		}
		else if (fireClock_.isDone())
		{
			float cX = x_ + width_ * 0.5f;
			float cY = y_ + height_ * 0.5f;
			float angleRadToTarget = this->angleRadTo(*target_);

			float speed = 7.0f;

			fireClock_.reset();
			bulletPool.add(
				new Bullet(
					cX, cY,
					speed * cosf(angleRadToTarget), speed * sinf(angleRadToTarget),
					10.0f,
					Image(16, 16, al_map_rgb(255, 255, 0)),
					1.0f,
					angleRadToTarget,
					0.0f,
					4.0f,
					false));
		}
	}

	for (auto it = bulletPool.cbegin(); it != bulletPool.cend(); it++)
	{
		if ((*it)->isFromPlayer() && this->isCollidingWith(**it))
		{
			(*it)->kill();
			this->hurt_((*it)->damage());
		}
	}

	float oldX = x_;
	float oldY = y_;

	x_ += velX_;
	y_ += velY_;

	switch (state_)
	{
	case State::Idle:
	{
		velX_ = 0.0f;
		velY_ = 0.0f;

		if (!player.isLive())
		{
			break;
		}
		else
		{
			target_ = &player;
			state_ = State::Attacking;
		}

		break;
	}
	case State::Attacking:
	{
		float distanceToTarget = this->distanceTo(*target_);

		if (distanceToTarget <= orbitDistance_)
		{
			state_ = State::Orbiting;
		}
		else if (distanceToTarget > attentionDistance_)
		{
			target_ = nullptr;
			state_ = State::Idle;
		}
		else
		{
			float angleRadToTarget = this->angleRadTo(*target_);

			velX_ = speed_ * cosf(angleRadToTarget);
			velY_ = speed_ * sinf(angleRadToTarget);
		}

		break;
	}
	case State::Orbiting:
	{
		float distanceToTarget = this->distanceTo(*target_);

		if (distanceToTarget <= retreatDistance_)
		{
			state_ = State::Retreating;
		}
		else if (distanceToTarget > (attackDistance_ + orbitDistance_) * 0.5f)
		{
			state_ = State::Attacking;
		}
		else
		{
			float angleRadToTarget = this->angleRadTo(*target_);
			float perpendicularRad = angleRadToTarget - Constants::PI * 0.5f;

			velX_ = speed_ * cosf(perpendicularRad);
			velY_ = speed_ * sinf(perpendicularRad);
		}

		break;
	}
	case State::Retreating:
	{
		float distanceToTarget = this->distanceTo(*target_);

		if (distanceToTarget > orbitDistance_)
		{
			state_ = State::Attacking;
		}
		else
		{
			float angleRadToTarget = this->angleRadTo(*target_);

			velX_ = speed_ * cosf(-angleRadToTarget);
			velY_ = speed_ * sinf(-angleRadToTarget);
		}

		break;
	}
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

void Enemy::render(const Camera &camera) const
{
	Character::render(camera);
	
	if (health_ < maxHealth_)
		healthBar_.render(
			x_ - camera.x() + width_ * 0.25f,
			y_ - camera.y() - 16.0f,
			width_ * 0.5f,
			8.0f);
}