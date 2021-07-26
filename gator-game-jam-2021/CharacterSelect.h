#pragma once

class Mouse;

#include <vector>
#include "CharacterAnimations.h"
#include "Button.h"

class CharacterSelect
{
private:
	std::vector<CharacterAnimations> animations_;
	std::vector<Button> buttons_;
	Button playButton_;
	size_t selectedIndex_;
public:
	CharacterSelect();

	void updateOnTick();
	void updateOnMouseAxes(const Mouse &mouse);
	void updateOnMousePress(const Mouse &mouse);

	void render() const;
};