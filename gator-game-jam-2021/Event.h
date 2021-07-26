#pragma once

#include "EventType.h"
#include "DriverState.h"
#include "CharacterAnimations.h"

class Event
{
protected:
	EventType eventType_;
public:
	Event(EventType eventType) :
		eventType_(eventType)
	{}

	virtual ~Event() {}

	inline EventType eventType() const
	{
		return eventType_;
	}
};

class EventChangeDriverState : public Event
{
private:
	DriverState driverState_;
public:
	EventChangeDriverState(DriverState driverState) :
		Event(EventType::ChangeDriverState),
		driverState_(driverState)
	{}

	inline DriverState driverState() const
	{
		return driverState_;
	}
};

class EventChangePlayerAnimations : public Event
{
private:
	CharacterAnimations animations_;
public:
	EventChangePlayerAnimations(const CharacterAnimations &animations) :
		Event(EventType::ChangePlayerAnimations),
		animations_(animations)
	{}

	inline const CharacterAnimations &animations() const
	{
		return animations_;
	}
};

class EventLoss : public Event
{
public:
	EventLoss() :
		Event(EventType::Loss)
	{}
};

class EventWin : public Event
{
public:
	EventWin() :
		Event(EventType::Win)
	{}
};