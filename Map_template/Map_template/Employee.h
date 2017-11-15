#pragma once
#include <string>
#include <ostream>

class Employee
{
private:
	
public:
	Employee(std::string name, std::string position, unsigned short age);
	~Employee();

	std::string name, position;
	unsigned short age;
};

std::ostream & operator<<(std::ostream & in, const Employee & emp);

