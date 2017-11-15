#include "Complex.hpp"
#include <iostream>

int main()
{
	Complex z1(2, 2);
	Complex z2(7, 6);
	bool h = z1 == z2;
	std::cout << z1 << " == " << z2 << " : " << h << std::endl;
	5 == z1;
	z1 == 5;
	std::cout << z1  / z2;
	Complex z3(1, 1);

	z3 * 10;
	10 * z3;

	std::cout << std::endl << "Faza : "
			   << (Complex(2,2)).getPhase()
		<< " " << (Complex(2,0)).getPhase()
		<< " " << (Complex(-2,2)).getPhase()
		<< " " << (Complex(0,2)).getPhase()
		<< " " << (Complex(-2,0)).getPhase()
		<< " " << (Complex(-2,-2)).getPhase()
		<< " " << (Complex(0,-2)).getPhase()
		<< " " << (Complex(2,-2)).getPhase()
		<< " " << (Complex(1, 5)).getPhase()
		<< " " << (Complex(-1, 5)).getPhase()
		<< " " << (Complex(-1,-5)).getPhase()
		<< " " << (Complex(1, -5)).getPhase();
	std::cout << std::endl << (z1+z2-z3*z1/z2);
	std::cout << std::endl << (z1+=z2-=z3*=z1/=z2);
	std::cout << std::endl << z1.getAmplitude() << std::endl;

	return 0;
}
