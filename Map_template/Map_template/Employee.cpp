#include "Employee.h"

Employee::Employee(std::string name, std::string position, unsigned short age) : name(name), position(position), age(age)
{
}


Employee::~Employee()
{
}

std::ostream & operator<<(std::ostream & in, const Employee & emp)
{
	in << "Name: " << emp.name << ", Position: " << emp.position << ", Age: " << emp.age;
	return in;
}
