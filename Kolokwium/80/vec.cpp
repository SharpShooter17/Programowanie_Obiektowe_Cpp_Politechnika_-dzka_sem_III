#include "vec.h"
#include <stdexcept>

Vect::Vect(unsigned int size) : size(size)
{
	vec = new double[size];
}

Vect::~Vect()
{
	delete[] vec;
}

void Vect::setElement(unsigned int index, double value)
{
	if (index >= size)
		throw std::out_of_range("Out of range");
	
	vec[index] = value;	
}

unsigned int Vect::getSize() 
{ 
	return this->size; 
}

double Vect::getMin()
{
	double result = vec[0];
	
	for (unsigned int i = 1; i < size; i++)
	{
		if (vec[i] < result)
			result = vec[i];
	}
	
	return result;
}

double Vect::getAverage()
{
	double sum = 0.0;
	
	for (unsigned int i = 0; i < size; i++)
		sum += vec[i];
	
	if (size == 0)
		throw std::string("Divide by zero");
	
	return sum / static_cast<double>(size);
}

std::ostream & operator<<(std::ostream & out, const Vect & v)
{
	out << "[";
	for (unsigned int i = 0; i < v.size; i++)
	{
		out << v.vec[i];
		if (i != (v.size - 1))
			out << ", ";
	}
	out << "]";
	return out;
}