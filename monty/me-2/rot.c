#include "monty.h"

void rotl(stack_t **stack, unsigned int line_number)
{
	if (*stack != NULL && (*stack)->next != NULL)
	{
		stack_t *last = *stack;
		stack_t *second_last = NULL;

		while (last->next != NULL)
		{
			second_last = last;
			last = last->next;
		}

		second_last->next = NULL;
		last->prev = NULL;
		last->next = *stack;
		(*stack)->prev = last;
		*stack = last;
	}
}

void rotr(stack_t **stack, unsigned int line_number)
{
	if (*stack != NULL && (*stack)->next != NULL)
	{
		stack_t *last = *stack;
		stack_t *second_last = NULL;

		while (last->next != NULL)
		{
			second_last = last;
			last = last->next;
		}

		second_last->next = NULL;
		last->prev = NULL;
		last->next = *stack;
		(*stack)->prev = last;
		*stack = last;
	}
}

int mode = 0;

void stack(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	mode = 0;
}

void queue(stack_t **stack, unsigned int line_number)
{
	(void)stack;
	(void)line_number;
	mode = 1;
}
