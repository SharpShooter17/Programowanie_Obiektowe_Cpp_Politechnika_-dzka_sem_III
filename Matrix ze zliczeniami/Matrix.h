/****************************************************
*													*
*	Created by Bartosz Ujazdowski					*
*													*
*				All right reserved © 2016			*
*													*
*													*
*****************************************************/

#ifndef H_MATRIX_H
#define H_MATRIX_H

#include <iosfwd>
#include <vector>
#include <initializer_list>
#include <iostream>
#include <fstream>
#include <cmath>
#include <stdexcept>
#include <string>

#include "Error.hpp"

template <typename T>
class CMatrix
{
public:

	template <typename S>
	class RefMatrix;
	
	/***************************Constructors*********************************/
	CMatrix();
	CMatrix(unsigned int row, unsigned int col);
	CMatrix(const CMatrix<T> & m);
	CMatrix(std::string path_to_file);
	CMatrix(std::initializer_list<std::initializer_list<T>> lst);
	CMatrix<T> & operator=(const CMatrix<T> & m);
	~CMatrix();

	/***************************Friends*************************************/
	template <typename S>
	friend	CMatrix<S> operator*(const T n, const CMatrix<S> & A);
	template <typename S>
	friend	std::ostream  & operator<<(std::ostream  & out, const CMatrix<S> & A);
	template <typename S>
	friend	std::istream  & operator>>(std::istream  & in, CMatrix<S> & A);
	template <typename S>
	friend	std::ifstream & operator>>(std::ifstream & in, CMatrix<S> & A);
	
	/***************************Operators**********************************/
	CMatrix<T>	operator*(const T n)			const;
	CMatrix<T>	operator*(const CMatrix<T> & A) const;
	CMatrix<T>	operator+(const CMatrix<T> & A) const;
	CMatrix<T>	operator-(const CMatrix<T> & A) const;
	CMatrix<T>	operator-()						const;

	/**************************Operators***********************************/
	CMatrix<T>	&	operator+=(const CMatrix<T> & A);
	CMatrix<T>	&	operator-=(const CMatrix<T> & A);
	CMatrix<T>	&	operator*=(const CMatrix<T> & A);
	CMatrix<T>	&	operator*=(const T A);

	T				operator()(unsigned int row, unsigned int col) const;			
	RefMatrix<T>	operator()(unsigned int row, unsigned int col)
	{
		return CMatrix<T>::RefMatrix<T>(*this, row, col);
	}

	/**************************Functions***********************************/
	CMatrix<T>				transposition()									const;
	CMatrix<T>				reverse()										const;
	CMatrix<T>				algebraicCoplement()							const;

	inline unsigned int		getRows()										const	{ return matrix_data->getRows(); }
	inline unsigned int		getColumns()									const	{ return  matrix_data->getColumns(); }
	inline T				getValue(unsigned row, unsigned col) const;
	void					setValue(unsigned row, unsigned col, T val);
	T						getDet()										const;

private:

	template <typename S>
	class MatrixDate;

	MatrixDate<T> *	matrix_data;

	T				det(CMatrix m)										const;
	CMatrix			removeRowAndCol(unsigned int row, unsigned int col) const;
};

template<typename T>
inline CMatrix<T>::CMatrix() : 
	matrix_data(new MatrixDate<T>(0, 0))
{
}

template <typename T>
CMatrix<T>::CMatrix(unsigned int row, unsigned int col) : 
	matrix_data( new MatrixDate<T>(row, col))
{
}

template <typename T>
CMatrix<T>::CMatrix(const CMatrix<T> & m) : 
	matrix_data(m.matrix_data)
{
	matrix_data->addN();
}

template<typename T>
CMatrix<T>::CMatrix(std::string path_to_file) : matrix_data(new MatrixDate<T>(0, 0))
{
	std::ifstream file;
	file.open(path_to_file.c_str(), std::ifstream::in);
	file.exceptions ( std::ifstream::failbit | std::ifstream::badbit | std::ifstream::eofbit );
	file >> *this;	
	file.close();
}

template<typename T>
CMatrix<T>::CMatrix(std::initializer_list<std::initializer_list<T>> lst) : 
	matrix_data(new MatrixDate<T>(static_cast<unsigned int>(lst.size()), static_cast<unsigned int>(lst.begin()->size())))
{
	int j = 0;
	for (auto p = lst.begin(); p != lst.end(); ++p)			//p is a row
	{
		int n = p->end() - p->begin();
		if (n != getColumns())				//If vector size is other than number of getColumns()...
			throw Matrix_Except::bad_initialize_list();

		for (int i = 0; i < n; i++)
			matrix_data->setValue(j, i, *(p->begin() + i));
		j++;
	}
}

template <typename T>
CMatrix<T> & CMatrix<T>::operator=(const CMatrix<T> & m)
{
	/*if (this->matrix_data->getN() == 1)
		this->matrix_data->assign(m.getRows(), m.getColumns(), m);
	else
	{
		MatrixDate<T> * tmp = new MatrixDate<T>(m.getRows(), m.getColumns());
		tmp->copy_date_from(*m.matrix_data);
		this->matrix_data->subN();
		this->matrix_data = tmp;
	}*/
	this->matrix_data->subN();
	if (this->matrix_data->getN() == 0)
		delete this->matrix_data;
	
	this->matrix_data = m.matrix_data;
	this->matrix_data->addN();

	return *this;
}


template <typename T>
CMatrix<T>::~CMatrix()
{
	matrix_data->subN();
	if (matrix_data->getN() == 0)
		delete matrix_data;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator*(const T n) const
{
	CMatrix A(getRows(), getColumns());

	for (unsigned i = 0; i < getRows(); i++)
		for (unsigned j = 0; j < getColumns(); j++)
			A.setValue(i, j, getValue(i, j) * n);

	return A;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T> & A) const
{
	/*Operation is unenforceable when numbers of getColumns() of matrix 
		is not equal number of getColumns() second matrix*/	
	if (!(this->getColumns() == A.getRows()))
		throw Matrix_Except::bad_size_matrixs();

	CMatrix<T> C(this->getRows(), this->getColumns());

	for (unsigned i = 0; i < this->getRows(); i++)
	{
		for (unsigned j = 0; j < this->getColumns(); j++)
		{
			T add = static_cast<T>(0);
			for (unsigned k = 0; k < A.getRows(); ++k)
			{
				add += this->getValue(i, k) * A.getValue(k, j);
			}
			C.setValue(i, j, add);
		}
	}

	return C;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix<T> & A) const
{
	if (!(this->getRows() == A.getRows() && this->getColumns() == A.getColumns()))
		throw Matrix_Except::other_size_of_matrixs();

	CMatrix<T> B(getRows(), getColumns());

	for (unsigned i = 0; i < getRows(); i++)
		for (unsigned j = 0; j < getColumns(); j++)
			B.setValue(i, j, getValue(i, j) + A.getValue(i, j));

	return B;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix<T> & A) const
{
	if (!(getRows() == A.getRows() && getColumns() == A.getColumns()))
		throw Matrix_Except::other_size_of_matrixs();
	
	CMatrix<T> B(getRows(), getColumns());

	for (unsigned i = 0; i < getRows(); i++)
		for (unsigned j = 0; j < getColumns(); j++)
			B.setValue(i, j, getValue(i, j) - A.getValue(i, j));

	return B;
}

template<typename T>
CMatrix<T> CMatrix<T>::operator-() const
{
	return *this * -1;
}

template<typename T>
CMatrix<T> & CMatrix<T>::operator+=(const CMatrix<T>& A)
{
	this->matrix_data = this->matrix_data->detach();

	*this = *this + A;	
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator-=(const CMatrix<T>& A)
{
	this->matrix_data = this->matrix_data->detach();
	
	*this = *this - A;
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator*=(const CMatrix<T>& A)
{
	this->matrix_data = this->matrix_data->detach();

	*this = *this * A;
	return *this;
}

template<typename T>
inline CMatrix<T>& CMatrix<T>::operator*=(const T A)
{
	this->matrix_data = this->matrix_data->detach();

	*this = *this * A;
	return *this;
}

template<typename T>
inline T CMatrix<T>::operator()(unsigned int row, unsigned int col) const
{
	return getValue(row, col);
}

template <typename T>
CMatrix<T> CMatrix<T>::transposition() const
{
	CMatrix B(getColumns(), getRows());

	for (unsigned i = 0; i < getRows(); i++)
		for (unsigned j = 0; j < getColumns(); j++)
			B.setValue(j, i, getValue(i, j));

	return B;
}

template <typename T>
CMatrix<T> CMatrix<T>::reverse() const
{
	T x = getDet();

	if (x == static_cast<T>(0)) 
		throw Matrix_Except::det_equal_0();

	x = static_cast<T>(1.0) / x;

	CMatrix<T> ret(this->algebraicCoplement().transposition());
	ret *= x;

	return ret;
}

template <typename T>
T CMatrix<T>::getValue(unsigned row, unsigned col) const
{
	return this->matrix_data->getValue(row, col);
}

template <typename T>
void CMatrix<T>::setValue(unsigned row, unsigned col, T val)
{
	this->matrix_data->setValue(row, col, val);
}

template <typename T>
T CMatrix<T>::getDet() const
{
	if (matrix_data->getRows() != matrix_data->getColumns())
		throw Matrix_Except::matrix_is_not_quadratic();

	return this->det(*this);
}

template <typename T>
T CMatrix<T>::det(CMatrix<T> m) const
{
	if (m.getColumns() != m.getRows()) 
		throw Matrix_Except::matrix_is_not_quadratic();

	if (m.getRows() == 2)
		return ((this->getValue(0, 0) * this->getValue(1, 1)) - (this->getValue(0, 1) * this->getValue(1, 0)));
	else if (m.getColumns() == 1) 
		return this->getValue(0, 0);

	T ret = static_cast<T>(0);

	for (unsigned i = 0; i < this->getRows(); i++)
	{
		int x = ((0 + i % 2) == 0) ? 1 : -1;
		ret += this->getValue(0, i) * static_cast<T>(x) * this->removeRowAndCol(0, i).getDet();
	}

	return ret;
}

template <typename T>
CMatrix<T> CMatrix<T>::removeRowAndCol(unsigned int row, unsigned int col) const
{
	if (row >= this->getRows() || col >= this->getColumns()) 
		throw std::out_of_range("Out of range");

	CMatrix<T> ret(getRows() - 1, getColumns() - 1);

	unsigned plus_k = 0;
	unsigned plus_l = 0;

	for (unsigned k = 0; k < ret.getRows(); k++)
	{
		if (k == row) plus_k = 1;

		for (unsigned l = 0; l < ret.getColumns(); l++)
		{
			if (l == col) plus_l = 1;
			ret.setValue(k, l, this->getValue(k + plus_k, l + plus_l));
		}
		plus_l = 0;
	}

	return ret;
}
template <typename T>
CMatrix<T> CMatrix<T>::algebraicCoplement() const
{
	CMatrix<T> ret(this->getRows(), this->getColumns());

	for (unsigned i = 0; i < ret.getRows(); ++i)
		for (unsigned j = 0; j < ret.getColumns(); ++j)
			ret.setValue(i, j, static_cast<T>(pow(-1, i + j)) * this->removeRowAndCol(i, j).getDet());

	return ret;
}

///Friends

template <typename T>
CMatrix<T> operator*(const T n, const CMatrix<T> & A)
{
	return A * n;
}

template <typename S>
std::ostream& operator<<(std::ostream &out, const CMatrix<S> & A)
{
	out << "row: " << A.getRows() << " col: " << A.getColumns() << std::endl;
	for (unsigned i = 0; i < A.getRows(); i++)
	{
		out << "| ";
		for (unsigned j = 0; j < A.getColumns(); j++)
		{
			out.width(6);
			out.fill('*');
			out << A.getValue(i, j) << " ";
		}
		out << "|\n";
	}

	return out;
}

template <typename S>
std::istream & operator>>(std::istream & in, CMatrix<S> & A)
{
	std::cout << "\n\nPodaj wartosc macierzy\n";

	for (unsigned i = 0; i < A.getRows(); i++)
	{
		for (unsigned j = 0; j < A.getColumns(); j++)
		{
			int value;
			
			do
			{
				if (in.fail())
				{
					in.clear();
					while (in.get() != '\n');
				}
				std::cout << "a( " << i << ", " << j << " ) = ";
			}
			while (!(in >> value));

			A.setValue(i, j, value);
		}
	}
	return in;
}

template<typename S>
std::ifstream & operator >> (std::ifstream & in, CMatrix<S> & A)
{
	unsigned int row;
	unsigned int col;

	in >> row >> col;

	A.matrix_data->resize_matrix(row, col);
	
	for (unsigned int i = 0; i < row; i++)
	{
		S tmp;
		for (unsigned int j = 0; j < col; j++)
		{
			in >> tmp;
			A.setValue(i, j, tmp);
		}
	}
		
	return in;
}

#include "RefMatrix.hpp"
#include "MatrixDate.hpp"

#endif