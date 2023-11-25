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
	info_t info[] = { INFO_INIT };
	int fd = 2;

	asm ("mov %1, %0\n\t"
		"add $3, %0"
		: "=r" (fd)
		: "r" (fd));

	if (argc == 2)
	{
		file_mode(argv, info);
	}
	populate_env_list(info);
	history_reading(info);
	execute_command(info, argv);
	return (EXIT_SUCCESS);
}
