#pragma once

class Keyboard;
class Mouse;
class ParticlePool;

#include "Pool.h"
#include "Listener.h"
#include "Enemy.h"
#include "Map.h"
#include "BulletPool.h"
#include "Player.h"
#include "Camera.h"

class Level : public Pool<Enemy>, public Listener
{
private:
	enum class State : uint8_t
	{
		Play,
		Win,
		Loss
	};

	ParticlePool &particlePool_;
	BulletPool bulletPool_;
	Map map_;
	Player *player_;
	CharacterAnimations enemyAnimations_;
	Camera camera_;
	State state_;
	unsigned int waveNum_;

	void spawnEnemies_(unsigned int numEnemies);
public:
	Level(
		const char *dataPath,
		const CharacterAnimations &playerAnimations,
		unsigned int maxNumEnemies);

	~Level();

	void onEvent(const Event &ev) override;

	void load(const char *dataPath, const CharacterAnimations &animations);

	void updateOnTick(const Keyboard &keyboard, const Mouse &mouse);
	void updateOnKeyPress(const Keyboard &keyboard);

	void render() const;

	const Player &player() const;
};