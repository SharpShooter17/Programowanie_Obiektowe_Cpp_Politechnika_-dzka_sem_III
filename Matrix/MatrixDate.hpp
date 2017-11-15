#pragma once

#include "Matrix.h"

#include <cstring>
#include <algorithm>

template<typename T>
class CMatrix<T>::MatrixDate
{
private:
	unsigned int rows;
	unsigned int cols;
	T ** matrix;
	unsigned int n;

	T** allocate_memory(unsigned int x, unsigned int y);
	inline void free_memory(T** & block, unsigned int x);
	inline void copy_memory(T** src, T ** dst, unsigned int row, unsigned int col);

public:
	MatrixDate(const MatrixDate &) = delete;
	MatrixDate & operator=(const MatrixDate &) = delete;

	MatrixDate(unsigned int rows, unsigned int cols);
	~MatrixDate();

	void copy_date_from(const MatrixDate & src);
	void resize_matrix(unsigned int rows, unsigned int cols);

	inline T getValue(unsigned int row, unsigned int col) const;
	void setValue(unsigned row, unsigned col, T val);

	inline unsigned int getRows() const;
	inline unsigned int getColumns() const;

	inline void addN() { n++; }
	inline void subN() { --n; }
	inline unsigned int getN() { return n; }

	void assign(unsigned int row, unsigned int col, const CMatrix & m);
	MatrixDate * detach()
	{
		if (this->getN() == 1)
			return this;

		MatrixDate * tmp = new MatrixDate(this->getRows(), this->getColumns());
		if (tmp == nullptr)
			throw Matrix_Except::no_memory();

		this->copy_memory(this->matrix, tmp->matrix, this->getRows(), this->getColumns());

		this->subN();
		
		return tmp;
	}
};

template<typename T>
T ** CMatrix<T>::MatrixDate::allocate_memory(unsigned int x, unsigned int y)
{
	T ** result = new T * [x];

	for (unsigned int i = 0; i < x; i++)
		result[i] = new T[y];

	return result;
}

template<typename T>
inline void CMatrix<T>::MatrixDate::free_memory(T **& block, unsigned int x)
{
	for (unsigned int i = 0; i < x; i++)
		delete[] block[i];
	delete[] block;
	block = nullptr;
}

template<typename T>
inline void CMatrix<T>::MatrixDate::copy_memory(T** src, T** dst, unsigned int row, unsigned int col)
{
	for (unsigned int i = 0; i < row; i++)
		std::memcpy(dst[i], src[i], col * sizeof(T));
}

template<typename T>
void CMatrix<T>::MatrixDate::resize_matrix(unsigned int rows, unsigned int cols)
{
	T** tmp = this->allocate_memory(rows, cols);
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
CMatrix<T>::MatrixDate::MatrixDate(unsigned int rows, unsigned int cols) :
	rows(rows),
	cols(cols),
	matrix(allocate_memory(this->rows, this->cols)),
	n(1)
{
}

template<typename T>
inline CMatrix<T>::MatrixDate::~MatrixDate()
{
	this->free_memory(this->matrix, this->rows);
}

template<typename T>
void CMatrix<T>::MatrixDate::copy_date_from(const MatrixDate & src)
{
	this->copy_memory(src.matrix, this->matrix, this->getRows(), this->getColumns());
}

template<typename T>
inline T CMatrix<T>::MatrixDate::getValue(unsigned int row, unsigned int col) const
{
	if (row >= this->getRows() || col >= this->getColumns())
		throw std::out_of_range("Out of range");
	
	return this->matrix[row][col];
}
template<typename T>
inline void CMatrix<T>::MatrixDate::setValue(unsigned row, unsigned col, T val)
{
	if (!(row < this->getRows() && col < this->getColumns()))
		throw std::out_of_range("Out of range");

	this->matrix[row][col] = val;
	return;
}

template<typename T>
inline unsigned int CMatrix<T>::MatrixDate::getRows() const
{
	return this->rows;
}

template<typename T>
inline unsigned int CMatrix<T>::MatrixDate::getColumns() const
{
	return this->cols;
}

template<typename T>
void CMatrix<T>::MatrixDate::assign(unsigned int row, unsigned int col, const CMatrix& m)
{
	if (this->getRows() != row || this->getColumns() != col)
	{
		T** tmp = this->allocate_memory(row, col);
		this->copy_memory(m.matrix_data->matrix, this->matrix, std::min({ row, this->getRows() }), std::min({ this->getColumns(), col }));
		this->free_memory(this->matrix, getRows());

		this->matrix = tmp;
	}
	else
	{
		this->copy_memory(m.matrix_data->matrix, this->matrix, row, col);
	}
}
