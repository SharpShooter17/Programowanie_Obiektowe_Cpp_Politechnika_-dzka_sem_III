#include <iostream>
#include "Employee.h"													//Defines class Employee
#include "Map.h"														//Defines template Map<Key, Value>

using namespace std;

int main(void) {
	typedef unsigned int ID; 											//Identification number of Employee
	Map<ID, Employee> database;											//Database of employees

	database.insert(761028073, Employee("Jan Kowalski", "salesman", 28)); 	//Add first employee: name: Jan Kowalski, position: salseman, age: 28,
	database.insert(510212881, Employee("Adam Nowak", "storekeeper", 54)); //Add second employee: name: Adam Nowak, position: storekeeper, age: 54
	database.insert(730505129, Employee("Anna Zaradna", "secretary", 32)); //Add third employee: name: Anna Zaradna, position: secretary, age: 32

	cout << database << endl;											//Print database

	Map<ID, Employee> newDatabase = database;							//Make a copy of database

	Employee* pE;
	pE = newDatabase[510212881];										//Find employee using its ID
	pE->position = "salesman";											//Modify the position of employee
	pE = newDatabase[761028073];										//Find employee using its ID
	pE->age = 29;														//Modify the age of employee

	database = newDatabase;												//Update original database

	cout << database << endl;											//Print original database
}