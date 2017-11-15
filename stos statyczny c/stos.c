#include <stdio.h>
#include "stos.h"

void push(stack_t * stack, int value)
{
	if (stack->size == stack->top)
	{
		printf("Brak pamieci\n");
		return;
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
		return stack->stack[0];
	}
	return stack->stack[--stack->top];
}

void clear(stack_t * stack)
{
	stack->top = 0;
	return;
}

bool isEmpty(stack_t * stack)
{
	return stack->top == 0 ? true : false;
}