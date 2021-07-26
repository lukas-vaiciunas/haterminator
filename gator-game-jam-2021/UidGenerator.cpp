#include "UidGenerator.h"

UidGenerator::UidGenerator() :
	next_(1)
{}

UidGenerator &UidGenerator::instance()
{
	static UidGenerator uidGenerator;
	return uidGenerator;
}

unsigned int UidGenerator::generate()
{
	unsigned int uid = 0;

	if (!released_.empty())
	{
		uid = released_.front();
		released_.pop();
	}
	else
	{
		uid = next_++;
	}

	return uid;
}

void UidGenerator::release(unsigned int uid)
{
	released_.push(uid);
}