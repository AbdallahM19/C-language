#include "monty.h"
/**
*my_pall - print out the stack
*
*@first: pointer of pointer to the stack
*
*@num: void int
*
*Return: void
*/
void my_pall(stack_t **first, unsigned int num)
{
stack_t *current = *first;
(void) num;
	if (first == NULL)
		return;
	while (current)
{
		printf("%d\n", current->n);
		current = current->next;
}
}
/**
*my_pint - print first element in stack
*
*@first: pointer of pointer to the stack
*
*@num: void int
*
*Return: void
*/
void my_pint(stack_t **first, unsigned int num)
{
	if (*first == NULL)
{
		fprintf(stderr, "L%u: can't pint, stack empty\n", num);
	if (args.file != NULL)
		fclose(args.file);
	if (args.buf != NULL)
		free(args.buf);
	if (*first != NULL)
		stack_free(*first);
	exit(EXIT_FAILURE);
	}
	printf("%d\n", (*first)->n);
}
