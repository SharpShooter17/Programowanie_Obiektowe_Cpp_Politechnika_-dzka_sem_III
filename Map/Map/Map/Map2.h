#pragma once
#include "Map_I.h"
class Map2 : public Map_I
{
public:

	virtual int operator[](std::string);
	virtual void insert(std::string, int) override;
};

