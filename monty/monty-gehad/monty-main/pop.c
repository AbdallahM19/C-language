#include "monty.h"
/**
*mypop - remove top element in stack
*
*@first: pointer of pointer to the stack
*
*@num: void int
*/
void mypop(stack_t **first, unsigned int num)
{
stack_t *current;
	if (*first == NULL)
{
		fprintf(stderr, "L%d: can't pop an empty stack\n", num);
		error(first);
}
	current = *first;
	*first = current->next;
	free(current);
}
