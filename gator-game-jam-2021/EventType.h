#pragma once

#include <cstdint>

enum class EventType : uint8_t
{
	ChangeDriverState,
	ChangePlayerAnimations,
	Loss,
	Win
};