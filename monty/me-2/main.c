#include "monty.h"

int main(int argc, char *argv[])
{
	// ... (existing code)

	char opcode[5]; // Assuming the maximum opcode length is 4 characters
	int value;

	while (fgets(line, sizeof(line), file) != NULL)
	{
		line_number++;
		if (line[0] == '#' || line[0] == '\n')
		{
			// Skip comments and empty lines
			continue;
		}

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
			// ... (existing opcode handling)
			else
			{
				fprintf(stderr, "L%d: unknown instruction %s\n", line_number, line);
				fclose(file);
				free(line);
				exit(EXIT_FAILURE);
			}
		}

		// ... (existing code)
	}

	// ... (existing code)

	return 0;
}
