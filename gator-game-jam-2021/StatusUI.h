#pragma once

class Player;

#include "Boundable.h"
#include "FillBar.h"

class StatusUI : public Boundable
{
private:
	FillBar healthBar_;
public:
	StatusUI(const AABB &bounds);

	void updateOnTick(const Player &player);

	void render() const;
};