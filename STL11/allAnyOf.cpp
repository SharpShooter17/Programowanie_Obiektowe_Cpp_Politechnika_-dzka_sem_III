#include<iostream>
#include<algorithm>
#include<vector>


int main()
{
	std::vector<int> data {1, 2, 3, 4, 5, 100};
	
	std::cout << std::all_of(data.begin(), data.end(), [](const int & i) { return i < 10; } ) << std::endl;
	std::cout << std::any_of(data.begin(), data.end(), [](const int & i) { return i < 10; } ) << std::endl;
	
	
	return 0;
}