#ifndef matrix_h
#define matrix_h

#include <stdio.h>

typedef struct {
	double ** matrix;
	int	size;
} matrix_t;


void showMatrix(const matrix_t * matrix);
matrix_t loadMatrix(const char * nameFile);
void freeMatrix(matrix_t * matrix);
double det(const matrix_t * matrix);

#endif
