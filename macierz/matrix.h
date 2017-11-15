#ifndef matrix_h
#define matrix_h

typedef struct {
  double **	matrix;
  int		size;
} matrix_t;


void		showMatrix(const matrix_t * const matrix);
matrix_t *	loadMatrix(const char * nameFile);
void		freeMatrix(matrix_t * matrix);
double		det(const matrix_t * const matrix);
#endif
