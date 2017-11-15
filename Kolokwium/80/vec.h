#pragma once
#include <ostream>

class Vect
{
private:
	double * vec;
	unsigned int size;
public:
	Vect() = delete;
	Vect(unsigned int);
	~Vect();
	unsigned int getSize(); 
	double getMin();
	double getAverage();
	void setElement(unsigned int index, double value);
	
	friend std::ostream & operator<<(std::ostream & out, const Vect & v);	
};