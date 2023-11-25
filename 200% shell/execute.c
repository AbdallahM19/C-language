#include "shell.h"

/**
 * execute_command - to check the input
 * @argument: the parameter & return argument struct
 * @argv: the argument vector from main()
 * Return: 0 or 1
*/
int execute_command(char *argument, char **command_argv, int *status)
{
	pid_t child_id = fork();

	if (child_id == 1)
		perror("");
	else if (child_id == 0)
	{
		if (execve(command, command_argv, environ) == -1)
		{
			*status = 2;
			perror("");
			exit(2);
		}
	}
	else if (child_id > 0)
	{
		if (wait(status) == -1)
			perror("");
		if (*status != 0)
			*status = 2;
	}
}