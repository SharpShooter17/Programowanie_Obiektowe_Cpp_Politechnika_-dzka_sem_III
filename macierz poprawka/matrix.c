#include "matrix.h"
#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>

void showMatrix(const matrix_t * matrix)
{
	for (int i = 0; i < matrix->size; ++i)
	{
		for (int j = 0; j < matrix->size; ++j)
		{
			printf("%.3lf\t", matrix->matrix[i][j]);
		}
		
		printf("\n");
	}
}

void allocMatrix(matrix_t * matrix, int size)
{
	matrix->size = size;
	matrix->matrix = (double**)malloc(sizeof(double*) * matrix->size);
	if (matrix->matrix == NULL)
	{
		printf("Error! Blada alokacji pamieci");
		exit(-1);
	}

	for (int i = 0; i < matrix->size; i++)
	{
		matrix->matrix[i] = (double*)malloc(sizeof(double) * matrix->size);

		if (matrix->matrix[i] == NULL)
		{
			printf("Error! Blad alokacji pamieci.");
			exit(-1);
		}
	}
}

void freeMatrix(matrix_t * matrix)
{
	for (int k = 0; k < matrix->size; ++k)
	{
		free(matrix->matrix[k]);
	}

	free(matrix->matrix);
	matrix->size = 0;
	matrix->matrix = NULL;
}

FILE * open_file(const char * fileName)
{
	FILE * file;
	file = fopen(fileName, "r");
	if (file == NULL)
	{
		printf("Error! Brak pamieci.");
		exit(-1);
	}
	
	return file;
}

matrix_t loadMatrix(const char * nameFile)
{
	FILE * file = open_file(nameFile);

	matrix_t result;

	int error = fscanf(file, "%d", &result.size);
	
	if (error == EOF)
	{
		printf("Error! Bledny plik!");

		fclose(file);
		exit(-3);
	}

	allocMatrix(&result, result.size);
	
	for (int i = 0; i < result.size; ++i)
	{
		for (int j = 0; j < result.size; ++j)
		{
			error = fscanf(file, "%lf", &result.matrix[i][j]);
			if (error == EOF)
			{
				printf("Error! Brak pamieci!");

				freeMatrix(&result);
				fclose(file);
				exit(-1);
			}
		}
	}
	
	fclose(file);
	return result;
}

matrix_t copy(const matrix_t * matrix)
{
	matrix_t res;

	allocMatrix(&res, matrix->size);
	
	for (int i = 0; i < matrix->size; ++i)
	{ 
		for (int j = 0; j < matrix->size; j++)
			res.matrix[i][j] = matrix->matrix[i][j];
	}

	res.size = matrix->size;
	return res;
}

matrix_t remove_Row_and_col(int row, int col, const matrix_t * matrix)
{
	matrix_t res;

	allocMatrix(&res, matrix->size - 1);

	unsigned plus_k = 0;
	unsigned plus_l = 0;

	for (unsigned k = 0; k < res.size; k++)
	{
		if (k == row) 
			plus_k = 1;

		for (unsigned l = 0; l < res.size; l++)
		{
			if (l == col) plus_l = 1;
			res.matrix[k][l] = matrix->matrix[k + plus_k][l + plus_l];
		}
		plus_l = 0;
	}

	return res;
}

double privat_det(const matrix_t * cmatrix)
{
	matrix_t matrix = copy(cmatrix);

	if (matrix.size == 2)
	{
		double res = ((matrix.matrix[0][0] * matrix.matrix[1][1]) - (matrix.matrix[0][1] * matrix.matrix[1][0]));
		freeMatrix(&matrix);
		return res;
	}
	else if (matrix.size == 1)
	{
		double res = matrix.matrix[0][0];
		freeMatrix(&matrix);
		return res;
	}

	double ret = 0.0;

	for (unsigned i = 0; i < matrix.size; i++)
	{
		int x = ((0 + i % 2) == 0) ? 1 : -1;
		matrix_t removed_rows = remove_Row_and_col(0, i, &matrix);
		ret += matrix.matrix[0][i] * x * privat_det(&removed_rows);
		freeMatrix(&removed_rows);
	}

	freeMatrix(&matrix);
	return ret;
}

double det(const matrix_t * matrix)
{
	if (matrix->size == 1)
		return matrix->matrix[0][0];

	matrix_t cop = copy(matrix);
	double res = privat_det(&cop);

	freeMatrix(&cop);
	return res;
}
