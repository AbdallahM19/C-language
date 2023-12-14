#include "monty.h"
/**
*stack_rotl - use it to rotate stack to the top
*@num: unsinged int
*@first: pointer of pointer to the stack
*/
void stack_rotl(stack_t **first, unsigned int num)
{
stack_t *current = *first, *seconed;
(void) num;
	if (!*first || !(*first)->next)
		return;
	seconed = (*first)->next;
	seconed->prev = NULL;
	while (current->next != NULL)
		current = current->next;
	current->next = *first;
	(*first)->next = NULL;
	(*first)->prev = current;
	*first = seconed;
}
/**
*stack_rotr - use it to rotate stack to the bottom
*@num: unsinged int
*@first: pointer of pointer to the stack
*/
void stack_rotr(stack_t **first, unsigned int num)
{
stack_t *current = *first;
(void) num;
	if (!*first || !(*first)->next)
		return;
	while (current->next != NULL)
		current = current->next;
	current->next = *first;
	current->prev->next = NULL;
	current->prev = NULL;
	(*first)->prev = current;
	*first = current;
}
