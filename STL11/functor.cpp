#include<iostream>

class Functor 
{
	public:
	int operator()(int a, int b)
	{
		return a + b;
	}
};

int main()
{
	Functor functor;
	std::cout << functor(2, 3) << std::endl;
	return 0;
}