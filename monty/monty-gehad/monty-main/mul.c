#include "monty.h"
/**
*stack_mul - mul of two top element
*@first: pointer of pointer to the stack
*@num: integer to be mul
*/
void stack_mul(stack_t **first, unsigned int num)
{
	stack_t *current = *first;

	if (*first == NULL || first == NULL || (*first)->next == NULL)
	{
		fprintf(stderr, "L%d: can't mul, stack too short\n", num);
		error(first);
	}
	current = *first;
	current->next->n *= current->n;
	*first = current->next;
	free(current);
}
