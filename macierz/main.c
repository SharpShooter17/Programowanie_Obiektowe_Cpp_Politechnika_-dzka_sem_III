#include "matrix.h"
#include <unistd.h> 
#include <fcntl.h> 
#include <stdio.h>

int file_exsist(const char * fileName)
{
  if (access(fileName, 0) != -1) {
    return 1;
  }
  else {
    return 0;
  }
}


int main(int argc, char *argv[])
{
  printf("argc: %d\n", argc);

  for (int i = 1; i < argc; i++)
  {
    if (file_exsist(argv[i]))
    {
      printf("File: %s:\n", argv[i]);
      matrix_t matrix = loadMatrix("matrix.txt");
      printf("Det: %lf\n", det(matrix));
      showMatrix(matrix);
      freeMatrix(matrix);
    }
    else
    {
      printf("File: %s not exist!\n", argv[i]);
    }
  }

  return 0;
}
