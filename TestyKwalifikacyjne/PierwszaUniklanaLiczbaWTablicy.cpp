#include <iostream>
#include <vector>
#include <algorithm>

/**
 * Dana jest tablica intów - znajdŸ pierwszy unikalny element.
 * 
 * Kompilacja: g++ -std=c++11 main.cpp -o app.exe
 */

int main()
{
	int tab[] = {2, 3, 2, 3, 7, 2, 6};
	std::vector<int> vec(tab, tab +  sizeof(tab) / sizeof(int) );	
	
	std::vector<int>::iterator it = std::find_if(vec.begin(), vec.end(), [&](int i){ return std::count(vec.begin(), vec.end(), i) == 1; });
	std::cout << "It: " << *it << " index: " << it - vec.begin();
	
	return 0;
}