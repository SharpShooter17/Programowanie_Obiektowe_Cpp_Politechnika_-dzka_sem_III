#include<iostream>
#include<vector>

int getData()
{
	return 3;
}

class Person
{
	void * data;
public:
	Person(){}
	Person( Person && person )
	{
		// move constructor;
		data = person.data;
		person.data = nullptr;
		std::cout << "Move constructor" << std::endl;
	}
};

Person createPerson()
{	
	Person obj;
	return obj;
}

int main()
{
	int x = 3;
	const int & lvalConst = getData();
	int && rValref = getData();
	int & lValRef = x;
	
	std::vector<Person> persons;
	
	persons.push_back(createPerson());
	
	
	return 0;
}