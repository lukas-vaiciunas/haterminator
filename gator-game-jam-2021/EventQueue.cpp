#include "EventQueue.h"
#include "Event.h"
#include "Listener.h"

EventQueue::~EventQueue()
{
	while (!events_.empty())
	{
		delete events_.front();
		events_.front() = nullptr;
	}
}

EventQueue &EventQueue::instance()
{
	static EventQueue eventQueue;
	return eventQueue;
}

void EventQueue::dispatch()
{
	if (events_.empty())
		return;

	Event *ev = events_.front();

	for (auto it = listeners_.cbegin(); it != listeners_.cend(); it++)
		if(it->second->isEventTypeAccepted(ev->eventType()))
			it->second->onEvent(*ev);

	delete ev;
	ev = nullptr;
	events_.pop();
}

void EventQueue::send(Event *ev)
{
	events_.push(ev);
}

void EventQueue::addListener(unsigned int uid, Listener *listener)
{
	listeners_.emplace(uid, listener);
}

void EventQueue::removeListener(unsigned int uid)
{
	listeners_.erase(uid);
}