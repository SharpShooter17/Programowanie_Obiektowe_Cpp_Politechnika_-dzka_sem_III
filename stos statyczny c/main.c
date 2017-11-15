#include <stdio.h>
#include "stos.h"

int main()
{
	stack_t stack;
	printf("Is empty: %d\n", isEmpty(&stack));
	push(&stack, 1);
	push(&stack, 12);
	push(&stack, 11);
	push(&stack, 12);
	push(&stack, 11);
	push(&stack, 11);
	printf("Is empty: %d\n", isEmpty(&stack));
	clear(&stack);
	printf("Is empty: %d\n", isEmpty(&stack));

	return 0;
}
