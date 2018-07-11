#include<iostream>
#include<initializer_list>
#include<vector>

class Numbers 
{
	std::vector<int> numbers;
	
public:
	Numbers(const std::initializer_list<int> & nums)
	{
		numbers = nums;
	}
};

int main()
{
	std::initializer_list<int> data = { 1, 2, 3, 4, 5}; // Tworzy tablicę liczb typu int
	std::cout << *data.begin() << std::endl;
	
	Numbers num({1,2,3});
	
	
	return 0;
}