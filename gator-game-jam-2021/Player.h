#pragma once

class Keyboard;
class Mouse;
class Map;
class BulletPool;

#include "Character.h"


class Player : public Character
{
public:
	Player(
		float x, float y,
		float health,
		float speed,
		float fireDelaySecs,
		const char *animationSheetPath,
		float scale);

	Player(
		float x, float y,
		float health,
		float speed,
		float fireDelaySecs,
		const CharacterAnimations &animations,
		float scale);

	void updateOnTick(
		const Keyboard &keyboard,
		const Mouse &mouse,
		const Map &map,
		const Camera &camera,
		BulletPool &bulletPool);
};