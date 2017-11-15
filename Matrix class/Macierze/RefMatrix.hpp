#pragma once

#include "Matrix.h"

template <class T>
class CMatrix<T>::RefMatrix<T> 
{
private:
	friend class CMatrix;
	CMatrix<T> & matrix;
	unsigned int rows;
	unsigned int cols;
	RefMatrix(CMatrix<T> & m);
public:
	template <class T>
	operator T() const;
	template <class T>
	CMatrix<T>::RefMatrix<T> operator=(T val);
};

template <class T>
CMatrix<T>::RefMatrix<T>::operator T() const
{
	return T(1);
}

template <class T>
CMatrix<T>::RefMatrix CMatrix<T>::RefMatrix(CMatrix<T> & m) : 
	matrix(m), 
	rows(m->rows), 
	cols(m->cols) 
{
}