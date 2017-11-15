#include "Map.h"
#include "Map2.h"
#include <iostream>

int main()
{
	Map m;
	Map2 m2;

	m.insert("test", 1);
	m.insert("Test", 2);
	m.insert("Test", 3);

	m2.insert("test", 1);
	m2.insert("Test", 2);
	m2.insert("Test", 5);

	std::cout << m << std::endl << m["Test"] << std::endl << std::endl;
	std::cout << m2 << std::endl << m2["Test"];

	return 0;
}