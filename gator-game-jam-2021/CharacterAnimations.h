#pragma once

#include <cstdint>
#include <unordered_map>
#include "Animation.h"

class CharacterAnimations
{
public:
	/*enum Roll : uint8_t
	{
		IdleFront = 0,
		IdleBack = 1,
		IdleRight = 2,
		IdleLeft = 3,
		WalkFront = 4,
		WalkBack = 5,
		WalkRight = 6,
		WalkLeft = 7
	};*/

	enum State : uint8_t
	{
		Idle = 1,
		Walk = 2
	};

	enum Roll : uint8_t
	{
		Front = 4,
		Back = 8,
		Right = 16,
		Left = 32
	};

	CharacterAnimations();
	CharacterAnimations(ALLEGRO_BITMAP *sheet, float frameSecs);

	void updateOnTick();

	void set(State state);
	void set(Roll roll);
	void set(State state, Roll roll);

	const Image &currentFrame() const;
private:
	//std::vector<Animation> rolls_;
	std::unordered_map<uint8_t, Animation> rolls_;
	State state_;
	Roll roll_;
};