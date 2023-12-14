#include "monty.h"
/**
*stack_div - divstarction of two top element
*@first: pointer of pointer to the stack
*@num: integer to be div
*/
void stack_div(stack_t **first, unsigned int num)
{
	stack_t *current = *first, *new = current->next;

	if (*first == NULL || first == NULL || (*first)->next == NULL)
	{
		fprintf(stderr, "L%d: can't div, stack too short\n", num);
		error(first);
	}
	if (current->n == 0)
		fprintf(stderr, "L%d: division by zero\n", num), error(first);
	new->n /= current->n;
	*first = new;
	free(current);
}
