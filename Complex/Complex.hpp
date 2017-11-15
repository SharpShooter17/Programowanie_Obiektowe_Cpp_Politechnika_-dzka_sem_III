#pragma once

#include <ostream>

class Complex
{
	double m_re;
	double m_im;
public:
	Complex(double re = 0.0, double im = 0.0);
	~Complex();

	inline double getRe() const;
	inline double getIm() const;
	double getPhase() const;
	double getAmplitude() const;

	Complex & operator+=(const Complex & complex);
	Complex & operator-=(const Complex & complex);
	Complex & operator*=(const Complex & complex);
	Complex & operator/=(const Complex & complex);

	Complex operator+(const Complex & complex) const;
	Complex operator-(const Complex & complex) const;
	Complex operator*(const Complex & complex) const;
	Complex operator/(const Complex & complex) const;
	
	friend std::ostream & operator<<(std::ostream & out, Complex const & complex);
};

bool operator==(const Complex & c1, const Complex & c2);

Complex operator+(double val, const Complex & complex);
Complex operator-(double val, const Complex & complex);
Complex operator*(double val, const Complex & complex);
Complex operator/(double val, const Complex & complex);