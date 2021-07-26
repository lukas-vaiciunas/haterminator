#include "Character.h"

#include <random>
#include "Camera.h"
#include "ParticlePool.h"

Character::Character(
	float x, float y,
	float health,
	float speed,
	float fireDelaySecs,
	const char *animationSheetPath,
	float scale)
	:
	Boundable(AABB(x, y, 16 * scale, 16 * scale)),
	health_(health),
	maxHealth_(health),
	velX_(0.0f),
	velY_(0.0f),
	speed_(speed),
	fireClock_(fireDelaySecs),
	animations_({}),
	scale_(scale),
	isLive_(true)
{
	ALLEGRO_BITMAP *animationSheet = al_load_bitmap(animationSheetPath);

	animations_ = CharacterAnimations(animationSheet, 0.15f);

	al_destroy_bitmap(animationSheet);
	animationSheet = nullptr;
}

Character::Character(
	float x, float y,
	float health,
	float speed,
	float fireDelaySecs,
	const CharacterAnimations &animations,
	float scale)
	:
	Boundable(AABB(x, y, 16 * scale, 16 * scale)),
	health_(health),
	maxHealth_(health),
	velX_(0.0f),
	velY_(0.0f),
	speed_(speed),
	fireClock_(fireDelaySecs),
	animations_(animations),
	scale_(scale),
	isLive_(true)
{}

void Character::render(const Camera &camera) const
{
	if (!isLive_)
		return;

	animations_.currentFrame().render(x_ - camera.x(), y_ - camera.y(), scale_);
}

float Character::health() const
{
	return health_;
}

float Character::maxHealth() const
{
	return maxHealth_;
}

bool Character::isLive() const
{
	return isLive_;
}

void Character::fixVelocity_()
{
	float speed = sqrtf(powf(velX_, 2.0f) + powf(velY_, 2.0f));

	if (speed > speed_)
	{
		float speedScale = speed_ / speed;

		velX_ *= speedScale;
		velY_ *= speedScale;
	}
}

void Character::selectAnimation_()
{
	if (velX_ > 0.0f)
	{
		animations_.set(
			CharacterAnimations::State::Walk,
			CharacterAnimations::Roll::Right);
	}
	else if (velX_ < 0.0f)
	{
		animations_.set(
			CharacterAnimations::State::Walk,
			CharacterAnimations::Roll::Left);
	}
	else if (velY_ > 0.0f)
	{
		animations_.set(
			CharacterAnimations::State::Walk,
			CharacterAnimations::Roll::Front);
	}
	else if (velY_ < 0.0f)
	{
		animations_.set(
			CharacterAnimations::State::Walk,
			CharacterAnimations::Roll::Back);
	}
	else
	{
		animations_.set(CharacterAnimations::State::Idle);
	}
}

void Character::hurt_(float damage)
{
	health_ -= damage;
	if (health_ <= 0.0f)
	{
		health_ = 0.0f;
		this->onDeath_();
	}
}

void Character::onDeath_()
{
	ParticlePool &particlePool = ParticlePool::instance();

	std::random_device rd;
	std::mt19937 eng(rd());

	std::uniform_real_distribution<float> velXDis(-3.0f, 3.0f);
	std::uniform_real_distribution<float> velYDis(-5.0f, -2.0f);

	float particleSize = 16.0f;
	float halfParticleSize = particleSize * 0.5f;

	isLive_ = false;
	
	for (unsigned int i = 0; i < 5; i++)
	{
		if (!particlePool.vacancy())
			break;

		particlePool.add(
			new Particle(
				x_ + width_ * 0.5f - halfParticleSize,
				y_ + height_ * 0.5f - halfParticleSize,
				velXDis(eng), velYDis(eng),
				0.0f, 0.2f,
				particleSize, particleSize,
				1.0f,
				1.0f,
				al_map_rgb(255, 0, 0)));
	}
}