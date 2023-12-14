#include "monty.h"

/**
 * push - Pushes a value onto the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void push(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (stack == NULL || *stack == NULL)
		exit(EXIT_FAILURE);
	if (head == NULL)
	{
		head = *stack;
		return;
	}
	temp = head;
	head = *stack;
	head->next = temp;
	temp->prev = head;
}

/**
 * pall - Prints all values in the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void pall(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (stack == NULL)
		exit(EXIT_FAILURE);
	temp = *stack;
	while (temp != NULL)
	{
		printf("%d\n", temp->n);
		temp = temp->next;
	}
}

/**
 * pop - Removes the top element of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void pop(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	if (stack == NULL || *stack == NULL)
		more_err(7, line_number);
	temp = *stack;
	*stack = temp->next;
	if (*stack != NULL)
		(*stack)->prev = NULL;
	free(temp);
}

/**
 * pint - Prints the value at the top of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void pint(stack_t **stack, unsigned int line_number)
{
	if (stack == NULL || *stack == NULL)
		more_err(6, line_number);
	printf("%d\n", (*stack)->n);
}

/**
 * nop - No operation; does nothing.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void nop(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
}

