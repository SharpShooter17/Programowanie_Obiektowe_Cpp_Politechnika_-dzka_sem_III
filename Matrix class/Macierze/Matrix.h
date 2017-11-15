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
#include "RefMatrix.hpp"

enum class Matrix_Except {	det_equal_0, 
							matrix_is_not_quadratic, 
							other_size_of_matrixs, 
							bad_size_matrixs, 
							bad_initialize_list,
						 };

template <typename T>
class CMatrix
{
public:
	template <class T> class RefMatrix<T>;
	
	/***************************Constructors*********************************/
	CMatrix();
	CMatrix(unsigned int row, unsigned int col);
	CMatrix(const CMatrix<T> & m);
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

	T				operator()(unsigned int row, unsigned int col) const;			//Read
	T			&	operator()(unsigned int row, unsigned int col);					//Write

	/**************************Functions***********************************/
	CMatrix<T>				transposition()									const;
	CMatrix<T>				reverse()										const;
	CMatrix<T>				algebraicCoplement()							const;

	inline unsigned int		getRows()										const	{ return rows; }
	inline unsigned int		getColumns()									const	{ return columns; }
	T						getValue(unsigned row, unsigned col) const;
	void					setValue(unsigned row, unsigned col, T val);
	T						getDet()										const;

private:
	unsigned int					rows;
	unsigned int					columns;
	std::vector<std::vector<T> >	matrix;

	T								det(CMatrix m)										const;
	CMatrix							removeRowAndCol(unsigned int row, unsigned int col) const;
};

template<typename T>
inline CMatrix<T>::CMatrix() : rows(0), columns(0)
{
}

template <typename T>
CMatrix<T>::CMatrix(unsigned int row, unsigned int col) : rows(row), columns(col)
{
	matrix.resize(row);

	for (unsigned i = 0; i < row; i++)
		matrix[i].resize(columns);
}

template <typename T>
CMatrix<T>::CMatrix(const CMatrix<T> & m)
	: rows{ m.getRows() }, columns{ m.getColumns() }
{
	/*matrix.resize(rows);
	for (unsigned i = 0; i < rows; i++)
		matrix[i].resize(columns);

	for (unsigned i = 0; i < m.getRows(); ++i)
		for (unsigned j = 0; j < m.getColumns(); ++j)
			setValue(i, j, m.getValue(i, j));*/
	matrix = m.matrix;			//przypisanie zaimplementowane w vector.h
}

template<typename T>
CMatrix<T>::CMatrix(std::initializer_list<std::initializer_list<T>> lst)
	: rows { static_cast<unsigned int>(lst.size()) }, columns { static_cast<unsigned int>(lst.begin()->size())}
{
	for (auto p = lst.begin(); p != lst.end(); ++p)			//p is a row
	{
		if ((p->end() - p->begin()) != columns)				//If vector size is other than number of columns...
			throw Matrix_Except::bad_initialize_list;

		matrix.push_back(std::vector<T>(p->begin(), p->end()));
	}
}

template <typename T>
CMatrix<T> & CMatrix<T>::operator=(const CMatrix<T> & m)
{
	//this->matrix.clear();
	this->columns = m.columns;
	this->rows = m.rows;
	
	/*this->matrix.resize(rows);

	for (unsigned i = 0; i < rows; i++)
		this->matrix[i].resize(columns);

	for (unsigned i = 0; i < this->getRows(); ++i)
		for (unsigned j = 0; j < this->getColumns(); ++j)
			this->setValue(i, j, m.getValue(i, j));*/

	this->matrix = m.matrix;

	return *this;
}


template <typename T>
CMatrix<T>::~CMatrix(){}

template <typename T>
CMatrix<T> CMatrix<T>::operator*(const T n) const
{
	CMatrix A(rows, columns);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			A.setValue(i, j, getValue(i, j) * n);

	return A;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator*(const CMatrix<T> & A) const
{
	/*Operation is unenforceable when numbers of columns of matrix 
		is not equal number of columns second matrix*/	
	if (!(columns == A.rows))
		throw Matrix_Except::bad_size_matrixs;

	CMatrix<T> C(rows, columns);

	for (unsigned i = 0; i < rows; i++)
	{
		for (unsigned j = 0; j < columns; j++)
		{
			T add = static_cast<T>(0);
			for (unsigned k = 0; k < A.rows; ++k)
			{
				add += getValue(i, k) * A.getValue(k, j);
			}
			C.setValue(i, j, add);
		}
	}

	return C;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator+(const CMatrix<T> & A) const
{
	if (!(this->rows == A.rows && this->columns == A.columns))
		throw Matrix_Except::other_size_of_matrixs;

	CMatrix<T> B(rows, columns);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			B.setValue(i, j, getValue(i, j) + A.getValue(i, j));

	return B;
}

template <typename T>
CMatrix<T> CMatrix<T>::operator-(const CMatrix<T> & A) const
{
	if (!(rows == A.rows && columns == A.columns))
		throw Matrix_Except::other_size_of_matrixs;
	
	CMatrix<T> B(rows, columns);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
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
	*this = *this + A;
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator-=(const CMatrix<T>& A)
{
	*this = *this - A;
	return *this;
}

template<typename T>
CMatrix<T>& CMatrix<T>::operator*=(const CMatrix<T>& A)
{
	*this = *this * A;
	return *this;
}
template<typename T>
inline CMatrix<T>& CMatrix<T>::operator*=(const T A)
{
	*this = *this * A;
	return *this;
}

template<typename T>
inline T CMatrix<T>::operator()(unsigned int row, unsigned int col) const
{
	return getValue(row - 1, col - 1);
}

template<typename T>
inline T & CMatrix<T>::operator()(unsigned int row, unsigned int col)
{
	row -= 1; col -= 1;

	if (row >= getRows() || col >= getColumns())
		throw std::out_of_range("Out of range");

	return matrix[row][col];
}


template <typename T>
CMatrix<T> CMatrix<T>::transposition() const
{
	CMatrix B(columns, rows);

	for (unsigned i = 0; i < rows; i++)
		for (unsigned j = 0; j < columns; j++)
			B.setValue(j, i, getValue(i, j));

	return B;
}

template <typename T>
CMatrix<T> CMatrix<T>::reverse() const
{
	T x = getDet();

	if (x == static_cast<T>(0)) throw Matrix_Except::det_equal_0;

	x = static_cast<T>(1.0) / x;

	CMatrix<T> ret(this->algebraicCoplement().transposition());
	ret *= x;

	return ret;
}

template <typename T>
T CMatrix<T>::getValue(unsigned row, unsigned col) const
{
	if (row >= getRows() || col >= getColumns())
		throw std::out_of_range("Out of range");

	return matrix[row][col];
}

template <typename T>
void CMatrix<T>::setValue(unsigned row, unsigned col, T val)
{
	if (!(row < rows && col < columns))
		throw std::out_of_range("Out of range");

	matrix[row][col] = val;
	return;
}

template <typename T>
T CMatrix<T>::getDet() const
{
	if (rows != columns) 
		throw Matrix_Except::matrix_is_not_quadratic;

	return det(*this);
}

template <typename T>
T CMatrix<T>::det(CMatrix<T> m) const
{
	if (m.getColumns() != m.getRows()) 
		throw Matrix_Except::matrix_is_not_quadratic;

	if (m.getRows() == 2)
		return ((matrix[0][0] * matrix[1][1]) - (matrix[0][1] * matrix[1][0]));
	else if (m.getColumns() == 1) 
		return matrix[0][0];

	T ret = static_cast<T>(0);

	for (unsigned i = 0; i < rows; i++)
	{
		int x = ((0 + i % 2) == 0) ? 1 : -1;
		ret += matrix[0][i] * static_cast<T>(x) * removeRowAndCol(0, i).getDet();
	}

	return ret;
}

template <typename T>
CMatrix<T> CMatrix<T>::removeRowAndCol(unsigned int row, unsigned int col) const
{
	if (row >= this->getRows() || col >= this->getColumns()) throw std::out_of_range("Out of range");

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
	out << "row: " << A.rows << " col: " << A.columns << std::endl;
	for (unsigned i = 0; i < A.rows; i++)
	{
		out << "| ";
		for (unsigned j = 0; j < A.columns; j++)
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
	std::cout << "\n\n\tPodaj wartosc macierzy\n";

	for (unsigned i = 0; i < A.getRows(); i++)
	{
		for (unsigned j = 0; j < A.getColumns(); j++)
		{
			int value;

			do
				std::cout << "\ta( " << i << ", " << j << " ) = ";
			while (!(in >> value));

			A.setValue(i, j, value);
		}
	}
	return in;
}

template<typename S>
inline std::ifstream & operator >> (std::ifstream & in, CMatrix<S> & A)
{
	std::string lineData;

	while (getline(in, lineData))
	{
		S tmp;
		std::vector<S> row;
		std::stringstream lineStream(lineData);

		while (lineStream >> tmp)
			row.push_back(tmp);

		A.matrix.push_back(row);
	}

	A.rows = static_cast<unsigned int>( A.matrix.size() );

	if (A.rows != 0)
		A.columns = static_cast<unsigned int>( A.matrix[0].size() );
	else
		A.columns = 0;

	return in;
}

#endif
