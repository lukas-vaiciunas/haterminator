#pragma once

class Keyboard;
class Mouse;

#include "Level.h"
#include "BulletPool.h"
#include "Player.h"
#include "Camera.h"
#include "StatusUI.h"
#include "EscapeMenuUI.h"

class Game
{
private:
	Level level_;
	StatusUI statusUI_;
	EscapeMenuUI escapeMenuUI_;
public:
	Game(const CharacterAnimations &animations);

	void updateOnTick(const Keyboard &keyboard, const Mouse &mouse);
	void updateOnMouseAxes(const Mouse &mouse);
	void updateOnMousePress(const Mouse &mouse);
	void updateOnKeyPress(const Keyboard &keyboard);

	void render() const;
};