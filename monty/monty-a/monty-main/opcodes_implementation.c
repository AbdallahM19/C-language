#include "monty.h"

/**
 * swap - Swaps the top two elements of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void swap(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "swap");
	temp = (*stack)->next;
	(*stack)->next = temp->next;
	if (temp->next != NULL)
		temp->next->prev = *stack;
	temp->next = *stack;
	(*stack)->prev = temp;
	temp->prev = NULL;
	*stack = temp;
}

/**
 * pchar - Prints the char at the top of the stack, followed by a new line.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void pchar(stack_t **stack, unsigned int line_number)
{
	int ascii;

	if (stack == NULL || *stack == NULL)
		string_err(11, line_number);
	ascii = (*stack)->n;
	if (ascii < 0 || ascii > 127)
		string_err(10, line_number);
	printf("%c\n", ascii);
}

/**
 * pstr - Prints the string starting at the top
 *		of the stack, followed by a new line.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void pstr(stack_t **stack, unsigned int line_number)
{
	int ascii;
	stack_t *temp;

	(void) line_number;
	if (stack == NULL || *stack == NULL)
	{
		printf("\n");
		return;
	}
	temp = *stack;
	while (temp != NULL)
	{
		ascii = temp->n;
		if (ascii <= 0 || ascii > 127)
			break;
		printf("%c", ascii);
		temp = temp->next;
	}
	printf("\n");
}

