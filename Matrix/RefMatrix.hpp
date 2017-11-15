#ifndef H_REFMATRIX_H
#define H_REFMATRIX_H

#include "Matrix.h"

template<typename T>
class CMatrix<T>::RefMatrix
{
private:
	friend class CMatrix<T>;
	CMatrix<T> & matrix;
	unsigned int row;
	unsigned int col;
	RefMatrix(CMatrix<T> & m, int row, int col);
public:
	operator T() const;
	RefMatrix & operator=(const RefMatrix & val)
	{
		return operator=( (T)val );
	}

	RefMatrix & operator=(T val)
	{
		this->matrix.matrix_data = this->matrix.matrix_data->detach();
		matrix.setValue(row, col, val);

		return *this;
	}	
};

template<typename T>
CMatrix<T>::RefMatrix::RefMatrix(CMatrix<T> &  m, int row, int col)  : 
	matrix(m), 
	row(row),
	col(col)
{
}

template<typename T>
CMatrix<T>::RefMatrix::operator T() const
{
	return matrix.getValue(row, col);
}

#endif