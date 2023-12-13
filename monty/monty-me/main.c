#include "monty.h"

int main(int argc, char *argv[])
{
	char opcode[5];
	int value;

	if (sscanf(line, "%4s %d", opcode, &value) == 1)
	{
		if (strcmp(opcode, "push") == 0)
		{
			push(&stack, value, line_number);
		}
		else if (strcmp(opcode, "pall") == 0)
		{
			pall(&stack, line_number);
		}
		else if (strcmp(opcode, "pint") == 0)
		{
			pint(&stack, line_number);
		}
		else if (strcmp(opcode, "pop") == 0)
		{
			pop(&stack, line_number);
		}
		else if (strcmp(opcode, "swap") == 0)
		{
			swap(&stack, line_number);
		}
		else if (strcmp(opcode, "add") == 0)
		{
			add(&stack, line_number);
		}
		else if (strcmp(opcode, "nop") == 0)
		{
			nop(&stack, line_number);
		}
		else
		{
			fprintf(stderr, "L%d: unknown instruction %s\n", line_number, line);
			fclose(file);
			free(line);
			exit(EXIT_FAILURE);
		}
	}
	return 0;
}