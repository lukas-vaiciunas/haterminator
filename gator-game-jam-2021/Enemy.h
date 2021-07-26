#pragma once

class Player;
class BulletPool;
class Map;

#include "Character.h"
#include "FillBar.h"

class Enemy : public Character
{
private:
	enum class State : uint8_t
	{
		Idle,
		Attacking,
		Orbiting,
		Retreating
	};

	const AABB *target_;
	FillBar healthBar_;
	State state_;
	float attackDistance_;
	float orbitDistance_;
	float retreatDistance_;
	float attentionDistance_;
public:
	Enemy(
		float x, float y,
		float attackDistance,
		float orbitDistance,
		float retreatDistance,
		float attentionDistance,
		float health,
		float speed,
		float fireDelaySecs,
		const char *animationSheetPath,
		float scale);

	Enemy(
		float x, float y,
		float attackDistance,
		float orbitDistance,
		float retreatDistance,
		float attentionDistance,
		float health,
		float speed,
		float fireDelaySecs,
		const CharacterAnimations &animations,
		float scale);

	void updateOnTick(const Player &player, const Map &map, BulletPool &bulletPool);

	void render(const Camera &camera) const override;
};