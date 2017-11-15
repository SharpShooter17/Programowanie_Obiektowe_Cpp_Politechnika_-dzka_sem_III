#ifndef stos_h
#define  stos_h

#include <stdbool.h>

typedef struct
{
	unsigned int size;
	unsigned int top;
	int stack[512];
} stack_t;

void push(stack_t * stack, int value);
int pop(stack_t * stack);
bool isEmpty(stack_t * stack);
void clear(stack_t * stack);

#endif
