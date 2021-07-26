#include "Listener.h"
#include "EventQueue.h"
#include "UidGenerator.h"

Listener::Listener(const std::unordered_set<EventType> &acceptedEventTypes) :
	acceptedEventTypes_(acceptedEventTypes),
	uid_(UidGenerator::instance().generate())
{
	EventQueue::instance().addListener(uid_, this);
}

Listener::~Listener()
{
	EventQueue::instance().removeListener(uid_);
}

bool Listener::isEventTypeAccepted(EventType eventType) const
{
	return acceptedEventTypes_.find(eventType) != acceptedEventTypes_.cend();
}