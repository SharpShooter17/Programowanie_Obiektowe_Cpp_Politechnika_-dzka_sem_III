#include "stack.hpp"
#include <iostream>

int main()
{
	stack stos;

	for (int i = 0; i < 256; i++) 
	{
		stos.push(i);
	}

	for (size_t i = 0; i < 257; i++) 
	{
		std::cout << stos.pop() << std::endl;
	}
	
	return 0;
}
