#include "Complex.hpp"
#include <cmath>

Complex::Complex(double re, double im) :
	m_re(re),
	m_im(im)
{
}

Complex::~Complex()
{
}

inline double Complex::getRe() const
{
	return m_re;
}

inline double Complex::getIm() const
{
	return m_im;
}

double Complex::getPhase() const
{
	double result = atan2(m_im, m_re) * 180.0/M_PI;

	if (result < 0.0)
		return 360 + result;
	else
		return result;
}

double Complex::getAmplitude() const
{
	return sqrt( m_re * m_re + m_im * m_im );
}

Complex & Complex::operator+=(const Complex & complex)
{
	m_re += complex.getRe();
	m_im += complex.getIm();
	return *this;
}

Complex & Complex::operator-=(const Complex & complex)
{
	m_re -= complex.getRe();
	m_im -= complex.getIm();
	return *this;
}

Complex & Complex::operator*=(const Complex & complex)
{
	m_re *= complex.getRe();
	m_re -= m_im * complex.getIm();
	m_im *= complex.getIm();
	m_im += m_im * complex.getRe();
	return *this;
}

Complex & Complex::operator/=(const Complex & complex)
{
	double re_help = (pow(complex.getRe(), 2) + pow(complex.getIm(), 2));
	if (re_help == 0.0) throw "Dzielenie przez zero jest nie dozwolone!";
	double im_help = (pow(complex.getRe(), 2) + pow(complex.getIm(), 2));
	if (im_help == 0.0) throw "Dzielenie przez zero jest nie dozwolone!";

	m_re = (m_re * complex.getRe() + m_im * complex.getIm()) / re_help;
	m_im = (m_im * complex.getRe() - m_re * complex.getIm()) / im_help;

	return *this;
}
Complex Complex::operator+(const Complex & complex) const
{
	return Complex(m_re + complex.getRe(), m_im + complex.getIm());
}

Complex Complex::operator-(const Complex & complex) const
{
	return Complex(m_re - complex.getRe(), m_im - complex.getIm());
}

Complex Complex::operator*(const Complex & complex) const
{
	return Complex( m_re * complex.getRe() - m_im * complex.getIm(), m_re * complex.getIm() + m_im * complex.getRe() );
}

Complex Complex::operator/(const Complex & complex) const
{
	double re_help = (pow(complex.getRe(), 2) + pow(complex.getIm(), 2));
	if (re_help == 0.0) throw "Dzielenie przez zero jest nie dozwolone!";
	double im_help = (pow(complex.getRe(), 2) + pow(complex.getIm(), 2));
	if (im_help == 0.0) throw "Dzielenie przez zero jest nie dozwolone!";

	return Complex((m_re * complex.getRe() + m_im * complex.getIm()) / re_help,
					(m_im * complex.getRe() - m_re * complex.getIm()) / im_help );
}

Complex operator+(double val, const Complex & complex)
{
	return complex + Complex(val, 0.0);
}

Complex operator-(double val, const Complex & complex)
{
	return Complex(val, 0.0) - complex;
}

Complex operator*(double val, const Complex & complex)
{
	return Complex(val, 0.0) * complex;
}

Complex operator/(double val, const Complex & complex)
{
	return Complex(val, 0.0) / complex;
}

bool operator==(const Complex & c1, const Complex & c2)
{
	return ( (c1.getIm() == c2.getIm()) && (c1.getRe() == c2.getRe()) ) ? true : false;
}

std::ostream & operator<<(std::ostream & out, Complex const & complex)
{
	out << complex.getRe() << " + " << complex.getIm() << "i";
	return out;
}
