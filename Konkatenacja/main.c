#include <stdio.h>
#include <malloc.h>
#include <string.h>
#include <assert.h>

char * lacz(const char * const string1, const char * const string2)
{
  int len = strlen(string1) + strlen(string2) + 1;
  
  char * result = (char*)malloc(len * sizeof(char));
  
  assert(result);

  strcpy(result, string1);
  strcat(result, string2);
  
  return result;
}

int main()
{
  char * string = lacz("Hello", ", world!\n");
  printf("%s", string);
  free(string);
  return 0;	
}
