#ifndef H_REFMATRIX_H
#define H_REFMATRIX_H

#include "Matrix.h"

template<typename T>
template<typename S>
class CMatrix<T>::RefMatrix
{
private:
	friend class CMatrix<T>;
	CMatrix<T> & matrix;
	unsigned int row;
	unsigned int col;
	RefMatrix(CMatrix<T> & m, int row, int col);
public:
	operator S() const;
	RefMatrix<S> & operator=(const RefMatrix<S> & val);
	RefMatrix<S> & operator=(S val);
};

template<typename T>
template<typename S>
CMatrix<T>::RefMatrix<S>::RefMatrix(CMatrix<T> &  m, int row, int col)  : 
	matrix(m), 
	row(row),
	col(col)
{
}

template<typename T>
template<typename S>
CMatrix<T>::RefMatrix<S>::operator S() const
{
	return matrix.getValue(row, col);
}

template<typename T>
template<typename S>
CMatrix<T>::RefMatrix<S> & CMatrix<T>::RefMatrix<S>::operator=(const CMatrix<T>::RefMatrix<S> & val)
{
	return operator=((S)val);
}

template<typename T>
template<typename S>
CMatrix<T>::RefMatrix<S> & CMatrix<T>::RefMatrix<S>::operator=(S val)
{
	if ( this->matrix.matrix_data->getN() != 1)
	{
		MatrixDate<T> * tmp = new MatrixDate<T>(matrix.getRows(), matrix.getColumns());
		tmp->copy_date_from(*matrix.matrix_data);
		this->matrix.matrix_data->subN();
		this->matrix.matrix_data = tmp;
	}

	matrix.setValue(row, col, val);

	return *this;
}

#endif