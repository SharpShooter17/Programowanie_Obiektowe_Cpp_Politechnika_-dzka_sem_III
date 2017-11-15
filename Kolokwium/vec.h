#pragma once
#include <ostream>

class Vect
{
private:
	double * vec;
	unsigned int size;
	Vect() {}
public:
	Vect(unsigned int);
	~Vect();
	unsigned int getSize(); 
	double getMin();
	double getAverage();
	void setElement(unsigned int index, double value);
	
	Vect operator+(Vect & v);
	Vect operator=(Vect & v);
	
	friend std::ostream & operator<<(std::ostream & out, const Vect & v);	
};