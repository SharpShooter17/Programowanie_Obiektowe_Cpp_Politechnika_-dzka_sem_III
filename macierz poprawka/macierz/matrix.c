#include "matrix.h"
#include <stdio.h>
#include <malloc.h>

void showMatrix(const matrix_t * const matrix)
{
  for (int i = 0; i < matrix->size; ++i)
  {
    for (int j = 0; j < matrix->size; ++j)
    {
      printf("%lf\t", matrix->matrix[i][j]);
    }
    printf("\n");
  }
}

void freeMatrix(matrix_t * matrix)
{
  for (int k = 0; k < matrix->size; ++k)
    free(matrix->matrix[k]);

  free(matrix->matrix);
  matrix->matrix = NULL;
  matrix->size = 0;
}

matrix_t * loadMatrix(const char * nameFile)
{
  //Otwieranie pliku
  FILE * file;
  file = fopen(nameFile, "r");
  if (file == NULL)
  {
    printf("Error! Brak pamieci.");

    return NULL;
  }

  //Tworzenie struktury
  matrix_t * result = (matrix_t*)malloc(sizeof(matrix_t));

  if (result == NULL)
  {
    printf("Error! Brak dostepu do pliku.");

    fclose(file);
    return NULL;
  }
  //ladowanie wielkosci macierzy
  int error = fscanf(file, "%d", &result->size);
  if ( error == EOF ) 
  {
    printf("Error! Bledny plik!");

    free(result);
    fclose(file);
    return NULL;
  }

  result->matrix = (double **)malloc(sizeof(double*) * result->size);
  if ( result->matrix == NULL )
  {
    printf("Error! Brak pamieci!");

    free(result->matrix);
    free(result);
    fclose(file);
    return NULL;
  }
  //Tworzenie tablicy
  for (int i = 0; i < result->size; ++i)
  {
    result->matrix[i] = (double*)malloc(sizeof(double)*result->size);
    if (result->matrix[i] == NULL )
    {
      printf("Error! Brak pamieci!");

      result->size = i;
      freeMatrix(result);
      free(result);
      fclose(file);
      return NULL;
    }
  }
  //ladowanie tablicy macierzy
  for (int i = 0; i < result->size; ++i)
  {
    for (int j = 0; j < result->size; ++j)
    {
      error = fscanf(file, "%lf", &result->matrix[i][j]);
      if ( error == EOF )
      {
	printf("Error! Brak pamieci!");
	
	freeMatrix(result);
	free(result);
	fclose(file);
	return NULL;
      }
    }
  }
  ///koniec
  fclose(file);

  return result;
}

matrix_t * copy(const matrix_t * const matrix)
{
  matrix_t * res = (matrix_t*)malloc(sizeof(matrix_t));
  res->matrix = (double**)malloc(sizeof(double*) * matrix->size);
  for (int i = 0; i < matrix->size; i++)
  {
    res->matrix[i] = (double*)malloc(sizeof(double) * matrix->size);
    for (int j = 0; j < matrix->size; j++)
    {
	    res->matrix[i][j] = matrix->matrix[i][j];
    }
  }

  res->size = matrix->size;
  return res;
}

matrix_t * remove_Row_and_col(int row, int col, const matrix_t * matrix)
{
  matrix_t * res = (matrix_t*)malloc(sizeof(matrix_t));
  res->matrix = (double**)malloc(sizeof(double*) * matrix->size);
  for (int i = 0; i < matrix->size - 1; i++)
  {
    res->matrix[i] = (double*)malloc(sizeof(double) * matrix->size);
  }
  res->size = matrix->size - 1;

  unsigned plus_k = 0;
  unsigned plus_l = 0;

  for (unsigned k = 0; k < res->size; k++)
  {
    if (k == row) plus_k = 1;

    for (unsigned l = 0; l < res->size; l++)
    {
	    if (l == col) plus_l = 1;
	    res->matrix[k][l] = matrix->matrix[k + plus_k][l + plus_l];
    }
    plus_l = 0;
  }

  return res;
}

double privat_det(const matrix_t * const cmatrix)
{
  matrix_t * matrix = copy(cmatrix);

  if (matrix->size == 2)
    return ((matrix->matrix[0][0] * matrix->matrix[1][1]) - (matrix->matrix[0][1] * matrix->matrix[1][0]));
  else if (matrix->size == 1) return matrix->matrix[0][0];

  double ret = 0.0;

  for (unsigned i = 0; i < matrix->size; i++)
  {
    int x = ((0 + i % 2) == 0) ? 1 : -1;
    ret += matrix->matrix[0][i] * x * privat_det( remove_Row_and_col(0, i, matrix) );
  }

  freeMatrix(matrix);

  return ret;
}

double det(const matrix_t * const matrix)
{
  if (matrix->size == 1)
	  return matrix->matrix[0][0];

  matrix_t * cop = copy(matrix);
  double res = privat_det(cop);

  free(cop);
  return res;
}
