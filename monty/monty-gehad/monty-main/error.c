#include "monty.h"
/**
*error - handle error
*@first: pointer of pointer to the stack
*/
void error(stack_t **first)
{
	if (args.file != NULL)
		fclose(args.file);
	if (args.buf != NULL)
		free(args.buf);
	if (*first != NULL)
		stack_free(*first);
	args.file = NULL;
	args.buf = NULL;
	*first = NULL;
	exit(EXIT_FAILURE);
}
