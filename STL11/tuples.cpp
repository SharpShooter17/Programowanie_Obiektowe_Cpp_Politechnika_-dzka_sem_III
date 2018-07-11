#include<iostream>
#include<tuple>
#include<string>

int main()
{
	std::tuple<int, double, std::string> example(1, 1.1, "Hello, World");
	std::cout << std::get<2>(example) << " " << std::get<0>(example) << std::get<1>(example) << std::endl;
	std::tuple<int, int, int> example1 {1, 2, 3};
	auto example2 = std::make_tuple(3, 4.3, "eo");
	return 0;
}