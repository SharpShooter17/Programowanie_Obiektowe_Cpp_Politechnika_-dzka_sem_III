#include <stdio.h>
#include "stos.h"

int main()
{
	stack_t stack;
	
	init(&stack);

	push(&stack, 1);
	push(&stack, 2);
	push(&stack, 3);
	push(&stack, 4);
	push(&stack, 5);

	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	printf("%d\n", pop(&stack));
	
	destroy(&stack);

	return 0;
}
