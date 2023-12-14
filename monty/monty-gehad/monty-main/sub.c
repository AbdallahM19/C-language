#include "monty.h"
/**
*stack_sub - substarction of two top element
*@first: pointer of pointer to the stack
*@num: integer to be sub
*/
void stack_sub(stack_t **first, unsigned int num)
{
	int sub;
	stack_t *current = *first;

	if (*first == NULL || first == NULL || (*first)->next == NULL)
	{
		fprintf(stderr, "L%d: can't sub, stack too short\n", num);
		error(first);
	}
	current = *first;
	sub = current->next->n - current->n;
	current->next->n = sub;
	*first = current->next;
	free(current);
}
