#include <stdio.h>
#include <malloc.h>
#include <stdlib.h>
#include <string.h>

#include "stos.h"

void push(stack_t * stack, int value)
{		
	if (stack->size == stack->top)
	{
		stack->stack = (int*)realloc(stack->stack, stack->size * 2 * sizeof(int));
		
		if (stack->stack == NULL)
			abort();
		
		stack->size *= 2;
	}

	stack->stack[stack->top] = value;
	stack->top++;
	
	return;
}

int pop(stack_t * stack)
{
	if (stack->top == 0)
	{
		printf("Stos jest pusty!\n");
		return 0;
	}

	return stack->stack[--stack->top];
}

void clear(stack_t * stack)
{
	stack->top = 0;
	return;
}

void init(stack_t * stack)
{
	stack->stack = (int*)malloc(sizeof(int));
	
	if (stack->stack == NULL)
		abort();
	
	stack->top = 0;
	stack->size = 1;
}

void destroy(stack_t * stack)
{
	free(stack->stack);
	stack->top = 0;
	stack->size = 0;
	stack->stack = NULL;
}

bool isEmpty(stack_t * stack)
{
	return stack->top == 0 ? true : false;
}