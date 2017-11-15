#include "Map.h"

int Map::operator[](std::string key)
{
	return get(key);
}

