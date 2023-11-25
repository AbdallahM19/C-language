#include "shell.h"
/**
 * main - start
 * 
 * @argc: count of arguments
 * 
 * @argv: arguments
 *
 * Return: 0
 */
int main(int argc, char **argv)
{
	struct_t argument[] = { ARGU_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		file_mode(argv, argument);
	}
	populate_env_list(argument);
	history_reading(argument);
	execute_command(argument, argv);
	return (EXIT_SUCCESS);
}
