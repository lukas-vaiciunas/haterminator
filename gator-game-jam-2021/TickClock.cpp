#include "TickClock.h"
#include "Config.h"

TickClock::TickClock(float targetSecs) :
	target_(static_cast<unsigned int>(targetSecs * Config::fps)),
	ticks_(0)
{}

void TickClock::updateOnTick()
{
	if (!this->isDone())
		ticks_++;
}

void TickClock::reset()
{
	ticks_ = 0;
}

bool TickClock::isDone() const
{
	return ticks_ >= target_;
}

unsigned int TickClock::target() const
{
	return target_;
}