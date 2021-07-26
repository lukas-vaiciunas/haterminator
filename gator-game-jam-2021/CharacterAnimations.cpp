#include "CharacterAnimations.h"

CharacterAnimations::CharacterAnimations() :
	state_(State::Idle),
	roll_(Roll::Front)
{}

CharacterAnimations::CharacterAnimations(ALLEGRO_BITMAP *sheet, float frameSecs) :
	rolls_(
		{
			{ State::Idle | Roll::Front, Animation(sheet, 0, 0, 16, 16, 2, frameSecs * 2.0f) },
			{ State::Idle | Roll::Back, Animation(sheet, 0, 16, 16, 16, 2, frameSecs * 2.0f) },
			{ State::Idle | Roll::Right, Animation(sheet, 0, 32, 16, 16, 2, frameSecs * 2.0f) },
			{ State::Idle | Roll::Left, Animation(sheet, 0, 48, 16, 16, 2, frameSecs * 2.0f) },
			{ State::Walk | Roll::Front, Animation(sheet, 32, 0, 16, 16, 6, frameSecs) },
			{ State::Walk | Roll::Back, Animation(sheet, 32, 16, 16, 16, 6, frameSecs) },
			{ State::Walk | Roll::Right, Animation(sheet, 32, 32, 16, 16, 6, frameSecs) },
			{ State::Walk | Roll::Left, Animation(sheet, 32, 48, 16, 16, 6, frameSecs) },
		}),
	state_(State::Idle),
	roll_(Roll::Front)
{}

void CharacterAnimations::updateOnTick()
{
	rolls_.at(state_ | roll_).updateOnTick();
}

void CharacterAnimations::set(State state)
{
	this->set(state, roll_);
}

void CharacterAnimations::set(Roll roll)
{
	this->set(state_, roll);
}

void CharacterAnimations::set(State state, Roll roll)
{
	if (state_ != state || roll_ != roll)
	{
		state_ = state;
		roll_ = roll;
		rolls_.at(state_ | roll_).reset();
	}
}

const Image &CharacterAnimations::currentFrame() const
{
	return rolls_.at(state_ | roll_).currentFrame();
}