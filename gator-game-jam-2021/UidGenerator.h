#pragma once

#include <queue>

class UidGenerator
{
private:
	std::queue<unsigned int> released_;
	unsigned int next_;

	UidGenerator();
	~UidGenerator() {}
public:
	UidGenerator(const UidGenerator &) = delete;
	UidGenerator &operator=(const UidGenerator &) = delete;

	static UidGenerator &instance();

	unsigned int generate();

	void release(unsigned int uid);
};