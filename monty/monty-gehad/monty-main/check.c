#include "monty.h"
/**
*check_func - itrate of the functions
*@buf: pointer
*@stack: pointer of pointer to the stack
*@num: unsigned int
*@file: the file open
*Return: integer
*/
int check_func(char *buf, stack_t **stack, unsigned int num, FILE *file)
{
instruction_t func[] = {
{"push", mypush},
{"pall", my_pall}, {"pint", my_pint},
{"pop", mypop}, {"add", stack_add},
{"nop", f_nop}, {"swap", f_swap},
{"sub", stack_sub}, {"div", stack_div},
{"mul", stack_mul}, {"mod", stack_mod},
{"pchar", stack_pchar}, {"pstr", stack_pstr},
{"stack", f_stack}, {"queue", f_queue},
{"rotl", stack_rotl}, {"rotr", stack_rotr},
{NULL, NULL}
};
	unsigned int x = 0;
	char *function = strtok(buf, " \n\t");

	if (function == NULL)
		return (0);
	if (function && function[0] == '#')
		return (0);
	args.buf = strtok(NULL, " \n\t");
	while (func[x].opcode && function)
{
		if (strcmp(function, func[x].opcode) == 0)
{
			func[x].f(stack, num);
			return (0);
}
		x++;
}
	if (function && func[x].opcode == NULL)
{
		fprintf(stderr, "L%d: unknown instruction %s\n", num, function);
		fclose(file), free(args.buf), fclose(args.file);
		stack_free(*stack), exit(EXIT_FAILURE);
}
	return (1);
}
