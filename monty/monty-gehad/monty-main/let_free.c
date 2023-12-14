#include "monty.h"
/**
*free_args - free struct of arguments
*@args: pointer to the struct
*Return: void
*/
void free_args(args_t *args)
{
	free(args->buf);
	free(args->file);
}
/**
*stack_free - free memory allocated for a stack
*@first: pointer to the stack
*Return: void
*/
void stack_free(stack_t *first)
{
stack_t  *current = first;
	while (first)
{
		current = first->next;
		free(first);
		first = current;
}
}
/**
*free_all - free all memorey
*@buf: 1 parameter
*@stack: 2 parameter
*@args: 3 parameter
*@file: 4 parameter
*/
void free_all(char *buf, stack_t *stack, args_t **args, FILE *file)
{
	free(buf);
	stack_free(stack);
	if (file != NULL)
		fclose(file);
	if (*args != NULL)
		free(*args);
	buf = NULL;
	stack = NULL;
	*args = NULL;
	file = NULL;
	exit(EXIT_FAILURE);
}
