#pragma once

class Event;

#include <unordered_set>
#include "EventType.h"

class Listener
{
private:
	std::unordered_set<EventType> acceptedEventTypes_;
	unsigned int uid_;
public:
	Listener(const std::unordered_set<EventType> &acceptedEventTypes);
	virtual ~Listener();

	virtual void onEvent(const Event &ev) = 0;

	bool isEventTypeAccepted(EventType eventType) const;
};