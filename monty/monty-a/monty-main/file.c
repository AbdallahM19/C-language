#include "monty.h"

/**
 * open_file - Opens and reads the content of the input file.
 * @file_name: Name of the input file.
 */
void open_file(char *file_name)
{
	FILE *fd = fopen(file_name, "r");

	if (file_name == NULL || fd == NULL)
		err(2, file_name);
	read_file(fd);
	fclose(fd);
}

/**
 * read_file - Reads and processes the content of the input file.
 * @fd: File descriptor of the input file.
 */
void read_file(FILE *fd)
{
	int line_number = 1, format = 0;
	char *buff = NULL;
	size_t i = 0;

	while (getline(&buff, &i, fd) != -1)
	{
		format = parse_line(buff, line_number, format);
		line_number++;
	}
	free(buff);
}

/**
 * parse_line - Parses a line from the input file.
 * @buffer: Line from the input file.
 * @line_number: Line number.
 * @format: Format flag (0 for stack, 1 for queue).
 * Return: the format flag after parsing the line.
 */
int parse_line(char *buffer, int line_number, int format)
{
	char *op_code, *value;
	const char *delimiter = "\n ";

	if (buffer == NULL)
		err(4);
	op_code = strtok(buffer, delimiter);
	if (op_code == NULL)
		return (format);
	value = strtok(NULL, delimiter);
	if (strcmp(op_code, "stack") == 0)
		return (0);
	if (strcmp(op_code, "queue") == 0)
		return (1);
	find_func(op_code, value, line_number, format);
	return (format);
}

/**
 * call_fun - Calls the appropriate function based on the opcode.
 * @func: Function pointer to the opcode function.
 * @op: Opcode.
 * @val: Value associated with the opcode.
 * @line_number: Line number of the opcode.
 * @format: Format flag (0 for stack, 1 for queue).
 */
void call_fun(op_func func, char *op, char *val, int line_number, int format)
{
	stack_t *node;
	int flag;
	int i;

	flag = 1;
	if (strcmp(op, "push") == 0)
	{
		if (val != NULL && val[0] == '-')
		{
			val = val + 1;
			flag = -1;
		}
		if (val == NULL)
			err(5, line_number);
		for (i = 0; val[i] != '\0'; i++)
		{
			if (isdigit(val[i]) == 0)
				err(5, line_number);
		}
		node = create_node(atoi(val) * flag);
		if (format == 0)
			func(&node, line_number);
		if (format == 1)
			add_queue(&node, line_number);
	}
	else
		func(&head, line_number);
}

