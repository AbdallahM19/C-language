#include "monty.h"

/**
 * add - Adds a node to the stack.
 * @stack: Pointer to the new node.
 * @line_number: Interger representing the line number of of the opcode.
 */
void add(stack_t **stack, unsigned int line_number)
{
	int i;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "add");

	(*stack) = (*stack)->next;
	i = (*stack)->n + (*stack)->prev->n;
	(*stack)->n = i;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}
/**
 * sub - Subtracts the top element from the second top element of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void sub(stack_t **stack, unsigned int line_number)
{
	int i;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "sub");

	(*stack) = (*stack)->next;
	i = (*stack)->n - (*stack)->prev->n;
	(*stack)->n = i;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * divide - Divides the second top element by the top element of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void divide(stack_t **stack, unsigned int line_number)
{
	int i;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "div");

	if ((*stack)->n == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	i = (*stack)->n / (*stack)->prev->n;
	(*stack)->n = i;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * mul - Multiplies the top two elements of the stack.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void mul(stack_t **stack, unsigned int line_number)
{
	int i;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mul");

	(*stack) = (*stack)->next;
	i = (*stack)->n * (*stack)->prev->n;
	(*stack)->n = i;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

/**
 * mod - Computes the remainder of the division
 *		of the second top element by the top element.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void mod(stack_t **stack, unsigned int line_number)
{
	int i;

	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		more_err(8, line_number, "mod");

	if ((*stack)->n == 0)
		more_err(9, line_number);
	(*stack) = (*stack)->next;
	i = (*stack)->n % (*stack)->prev->n;
	(*stack)->n = i;
	free((*stack)->prev);
	(*stack)->prev = NULL;
}

