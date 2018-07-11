#include <array>
#include <iostream>

int main()
{
	std::array<int, 10> arr = {2, 23};
	arr.fill(0);
	
	for (auto & item : arr)
	{
		std::cout << item << std::endl;
	}
	
	std::cout << arr.size() << " " << arr.at(0);
	
	return 0;
}