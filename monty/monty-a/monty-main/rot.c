#include "monty.h"

/**
 * rotl - Rotates the stack to the top.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void rotl(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;
	temp = *stack;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = *stack;
	(*stack)->prev = temp;
	*stack = (*stack)->next;
	(*stack)->prev->next = NULL;
	(*stack)->prev = NULL;
}

/**
 * rotr - Rotates the stack to the bottom.
 * @stack: Double pointer to the stack.
 * @line_number: Line number of the opcode.
 */
void rotr(stack_t **stack, unsigned int line_number)
{
	stack_t *temp;

	(void) line_number;
	if (stack == NULL || *stack == NULL || (*stack)->next == NULL)
		return;
	temp = *stack;
	while (temp->next != NULL)
		temp = temp->next;
	temp->next = *stack;
	temp->prev->next = NULL;
	temp->prev = NULL;
	(*stack)->prev = temp;
	(*stack) = temp;
}

