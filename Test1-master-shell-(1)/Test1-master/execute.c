#include "shell.h"
/**
* execute_command - to check the input
* 
* @argument: the parameter & return argument struct
*
* @argv: the argument vector from main()
*
* Return: 0 or 1
*/
int execute_command(struct_t *argument, char **argv)
{
	ssize_t r = 0;
	int x = 0;

	while (r != -1 && x != -2)
	{
		delete_argument(argument);
		if (interactive_mode(argument))
			_puts("$ ");
		_eputchar(NEGATTIVE);
		r = get_input(argument);
		if (r != -1)
		{
			init_argument(argument, argv);
			x = check_builtin(argument);
			if (x == -1)
				command_placeholder(argument);
		}
		else if (interactive_mode(argument))
			_putchar('\n');
		free_argument(argument, 0);
	}
	history_writing(argument);
	free_argument(argument, 1);
	if (!interactive_mode(argument) && argument->status)
		exit(argument->status);
	if (x == -2)
	{
		if (argument->err_num == -1)
			exit(argument->status);
		exit(argument->err_num);
	}
	return (x);
}
/**
 * fork_command( - fork to execute a command
 * 
 * @argument: pointer to thw struct
 *
 * Return: void
 */
void fork_command(struct_t *argument)
{
	pid_t child;

	child = fork();
	if (child == -1)
	{
		perror("Error:");
		return;
	}
	if (child == 0)
	{
		if (execve(argument->path, argument->argv, get_environ(argument)) == -1)
		{
			free_argument(argument, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(argument->status));
		if (WIFEXITED(argument->status))
		{
			argument->status = WEXITSTATUS(argument->status);
			if (argument->status == 126)
				print_error(argument, "Permission denied\n");
		}
	}
}
/**
* file_mode - to execute from a file
*
*@av: argument
*
*@argument: pointer to the struct
*
*Return: which in the file
*/
int file_mode(char **av, struct_t *argument)
{
    	int fd = open(av[1], O_RDONLY);
		if (fd == -1)
		{
			if (errno == EACCES)
				exit(126);
			if (errno == ENOENT)
			{
				_eputs(av[0]);
				_eputs(": 0: Can't open ");
				_eputs(av[1]);
				_eputchar('\n');
				_eputchar(NEGATTIVE);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		argument->readfd = fd;
        return (EXIT_SUCCESS);
}