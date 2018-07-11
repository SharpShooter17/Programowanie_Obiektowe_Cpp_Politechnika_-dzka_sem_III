#include<iostream>
#include<functional>
#include <algorithm>
 
// Function that accepts no parameter
// It is to break the recursion chain of vardiac template function
void log()
{
}
 
/*
 * Variadic Template Function that accepts variable number
 * of arguments of any type.
 */
template<typename T, typename ... Args>
void log(T first, Args ... args) {
 
	// Print the First Element
	std::cout<<first<<" , ";
 
	// Forward the remaining arguments
	log(args ...);
}
int add(int a, int b)
{
	return a + b;
}

int main()
{
	auto fun = std::bind(add, std::placeholders::_1, std::placeholders::_2);
	std::cout << fun(1,2) << std::endl;
	
	auto addTo3 = std::bind(add, 3, std::placeholders::_1);
	std::cout << addTo3(3) << std::endl;
	
	log(2, 3.4, "aaa");
	
	return 0;
}