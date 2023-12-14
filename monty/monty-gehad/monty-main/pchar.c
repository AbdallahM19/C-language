#include "monty.h"
/**
*stack_pchar - print first char in stack
*
*@first: pointer of pointer to the stack
*
*@num: void int
*/
void stack_pchar(stack_t **first, unsigned int num)
{
	if (!*first)
		fprintf(stderr, "L%d: can't pchar, stack empty\n", num), error(first);
	if ((*first)->n > 127 || (*first)->n < 0)
{
		fprintf(stderr, "L%d: can't pchar, value out of range\n", num);
		error(first);
}
	printf("%c\n", (*first)->n);
}
/**
*stack_pstr - print string
*@first: pointer of pointer to the stack
*
*@num: void int
*/
void stack_pstr(stack_t **first, unsigned int num)
{
(void) num;
	while (*first)
{
		if ((*first)->n > 127 || (*first)->n < 0)
			break;
		printf("%c", (*first)->n);
	*first = (*first)->next;
}
	printf("\n");
}
