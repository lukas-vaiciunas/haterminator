#pragma once

#include <cstdint>

enum class DriverState : uint8_t
{
	None,
	Menu,
	CharacterSelect,
	Play,
	Quit
};