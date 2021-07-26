#pragma once

class Event;
class Listener;

#include <queue>
#include <unordered_map>

class EventQueue
{
private:
	std::queue<Event *> events_;
	std::unordered_map<unsigned int, Listener *> listeners_;

	EventQueue() {}
	~EventQueue();
public:
	EventQueue(const EventQueue &) = delete;
	EventQueue &operator=(const EventQueue &) = delete;

	static EventQueue &instance();

	void dispatch();

	void send(Event *ev);

	void addListener(unsigned int uid, Listener *listener);
	void removeListener(unsigned int uid);
};