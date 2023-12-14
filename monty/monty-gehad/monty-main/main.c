#include "monty.h"
args_t args = {NULL, NULL, 0};
/**
*main - entry point to the interpreter
*@argc: number of arguments
*@argv: array of arguments
*Return: 0
*/
int main(int argc, char **argv)
{
char *buf = NULL;
size_t buf_size = 0;
ssize_t read_line = 1;
unsigned int count = 0;
stack_t *stack = NULL;
FILE *file;
args_t *args;
	if (argc != 2)
		fprintf(stderr, "USAGE: monty file\n"), exit(EXIT_FAILURE);
	file = fopen(argv[1], "r");
	if (file == NULL)
{
		fprintf(stderr, "Error: can't open file %s\n", argv[1]);
		exit(EXIT_FAILURE);
}
	args = malloc(sizeof(args_t));
	if (args == NULL)
	{
		fprintf(stderr, "Error: malloc failed\n");
		fclose(file), file = NULL, exit(EXIT_FAILURE);
	}
	args->file = file;
	while (read_line > 0)
{
		read_line = getline(&buf, &buf_size, file);
		args->buf = buf, count++;
		if (read_line > 0)
			check_func(buf, &stack, count, file);
}
	free_all(buf, stack, &args, file);
	buf = NULL;
	stack = NULL;
	args = NULL;
	file = NULL;
	return (0);
}
