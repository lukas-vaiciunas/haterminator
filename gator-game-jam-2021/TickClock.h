#pragma once

class TickClock
{
private:
	unsigned int ticks_;
	unsigned int target_;
public:
	TickClock(float targetSecs);

	void updateOnTick();

	void reset();

	bool isDone() const;
	unsigned int target() const;
};