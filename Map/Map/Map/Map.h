#pragma once
#include "Map_I.h"

class Map :	public Map_I
{
public:
	virtual int operator[](std::string);
};

