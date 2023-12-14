#include "monty.h"
/**
*f_swap - swap the two top element
*@num: unsinged int
*@first: pointer of pointer to the stack
*/
void f_swap(stack_t **first, unsigned int num)
{
stack_t *current = *first, *new = current->next;
	if (*first == NULL || first == NULL || (*first)->next == NULL)
{
		fprintf(stderr, "L%d: can't swap, stack too short\n", num);
		error(first);
}
	current->prev = new;
	current->next = new->next;
	new->prev = NULL;
	new->next = current;
	*first = new;
}
