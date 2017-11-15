#pragma once

#include "Matrix.h"

#include <cstring>
#include <algorithm>

template<typename T>
template<typename S>
class CMatrix<T>::MatrixDate
{
private:
	unsigned int rows;
	unsigned int cols;
	S ** matrix;
	unsigned int n;

	S** allocate_memory(unsigned int x, unsigned int y);
	inline void free_memory(S** & block, unsigned int x);
	inline void copy_memory(S** src, S ** dst, unsigned int row, unsigned int col);

public:
	MatrixDate(const MatrixDate<S> &) = delete;
	MatrixDate<S> & operator=(const MatrixDate<S> &) = delete;

	MatrixDate(unsigned int rows, unsigned int cols);
	~MatrixDate();

	void copy_date_from(const MatrixDate<S> & src);
	void resize_matrix(unsigned int rows, unsigned int cols);

	inline S getValue(unsigned int row, unsigned int col) const;
	void setValue(unsigned row, unsigned col, T val);

	inline unsigned int getRows() const;
	inline unsigned int getColumns() const;

	inline void addN() { n++; }
	inline void subN() { --n; }
	inline unsigned int getN() { return n; }

	void assign(unsigned int row, unsigned int col, const CMatrix<S> & m);
	MatrixDate<S> * detach()
	{
		if (this->n == 1)
			return this;

		MatrixDate<S> * tmp = new MatrixDate<S>(this->getRows(), this->getColumns());
		if (tmp == nullptr)
			throw Matrix_Except::no_memory();

		this->copy_memory(tmp->matrix, this->matrix, this->getRows(), this->getColumns());

		this->subN();

		return tmp;
	}
};

template<typename T>
template<typename S>
S ** CMatrix<T>::MatrixDate<S>::allocate_memory(unsigned int x, unsigned int y)
{
	S ** result = new S*[x];

	if (result == nullptr)
		throw Matrix_Except::no_memory();

	for (unsigned int i = 0; i < x; i++)
		if ((result[i] = new S[y]) == nullptr)
			throw Matrix_Except::no_memory();

	return result;
}

template<typename T>
template<typename S>
inline void CMatrix<T>::MatrixDate<S>::free_memory(S **& block, unsigned int x)
{
	for (unsigned int i = 0; i < x; i++)
		delete[] block[i];
	delete[] block;
	block = nullptr;
}

template<typename T>
template<typename S>
inline void CMatrix<T>::MatrixDate<S>::copy_memory(S** src, S** dst, unsigned int row, unsigned int col)
{
	for (unsigned int i = 0; i < row; i++)
		std::memcpy(dst[i], src[i], col * sizeof(S));
}

template<typename T>
template<typename S>
void CMatrix<T>::MatrixDate<S>::resize_matrix(unsigned int rows, unsigned int cols)
{
	S** tmp = this->allocate_memory(rows, cols);
	this->copy_memory(this->matrix, tmp, std::min({ this->getRows(),rows }), std::min({ this->getColumns(), cols }));

	if (this->getN() == 1)
		free_memory(this->matrix, this->getColumns());
	else
		this->subN();

	this->matrix = tmp;
	this->rows = rows;
	this->cols = cols;
}

template<typename T>
template<typename S>
CMatrix<T>::MatrixDate<S>::MatrixDate(unsigned int rows, unsigned int cols) :
	rows(rows),
	cols(cols),
	matrix(allocate_memory(rows, cols)),
	n(1)
{
}

template<typename T>
template<typename S>
inline CMatrix<T>::MatrixDate<S>::~MatrixDate()
{
	this->free_memory(this->matrix, this->rows);
}

template<typename T>
template<typename S>
void CMatrix<T>::MatrixDate<S>::copy_date_from(const MatrixDate<S> & src)
{
	this->copy_memory(src.matrix, this->matrix, this->getRows(), this->getColumns());
}

template<typename T>
template<typename S>
inline S CMatrix<T>::MatrixDate<S>::getValue(unsigned int row, unsigned int col) const
{
	if (row >= this->getRows() || col >= this->getColumns())
		throw std::out_of_range("Out of range");

	return this->matrix[row][col];
}
template<typename T>
template<typename S>
inline void CMatrix<T>::MatrixDate<S>::setValue(unsigned row, unsigned col, T val)
{
	if (!(row < this->getRows() && col < this->getColumns()))
		throw std::out_of_range("Out of range");

	this->matrix[row][col] = val;
	return;
}

template<typename T>
template<typename S>
inline unsigned int CMatrix<T>::MatrixDate<S>::getRows() const
{
	return this->rows;
}

template<typename T>
template<typename S>
inline unsigned int CMatrix<T>::MatrixDate<S>::getColumns() const
{
	return this->cols;
}

template<typename T>
template<typename S>
void CMatrix<T>::MatrixDate<S>::assign(unsigned int row, unsigned int col, const CMatrix<S>& m)
{
	if (this->getRows() != row || this->getColumns() != col)
	{
		S** tmp = this->allocate_memory(row, col);
		this->copy_memory(m.matrix_data->matrix, this->matrix, std::min({ row, this->getRows() }), std::min({ this->getColumns(), col }));
		this->free_memory(this->matrix, getRows());

		this->matrix = tmp;
	}
	else
	{
		this->copy_memory(m.matrix_data->matrix, this->matrix, row, col);
	}
}
