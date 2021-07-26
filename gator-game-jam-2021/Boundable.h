#pragma once

#include "AABB.h"

class Boundable : public AABB
{
public:
	Boundable(const AABB &bounds);
	virtual ~Boundable() {}
};