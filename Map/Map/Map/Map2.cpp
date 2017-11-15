#include "Map2.h"
#include <algorithm>
#include <string>

int Map2::operator[](std::string key)
{
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	return get(key);
}

void Map2::insert(std::string key, int value)
{
	std::transform(key.begin(), key.end(), key.begin(), ::tolower);
	Map_I::insert(key, value);
}