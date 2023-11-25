#include "shell.h"

/**
 * my_exit - exit the program (Handles the 'exit' command)
 * @argument: structure contain argumentrmation
 * Return:
 * -2: specified exit status.
 * 1: an illegal number as the exit status.
*/
int my_exit(struct_t*argument)
{
	int exit_check;

	if (argument->argv[1])
	{
		exit_check = convert_string(argument->argv[1]);
		if (exit_check == -1)
		{
			argument->status = 2;
			print_error(argument, "Illegal number: ");
			_eputs(argument->argv[1]);
			_eputchar('\n');
			return (1);
		}
		argument->err_num = convert_string(argument->argv[1]);
		return (-2);
	}
	argument->err_num = -1;
	return (-2);
}

/**
 * my_cd - changes the current directory of the process.
 * @argument: structure contain argumentrmation
 * Return: Always 0
*/
int my_cd(struct_t *argument)
{
	char *curr_dir, *dir, buffer[1024];
	int chdir_ret;

	curr_dir = getcwd(buffer, 1024);
	if (!curr_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!argument->argv[1])
	{
		dir = _getenv(argument, "HOME=");
		if (!dir)
			chdir_ret = chdir((dir = _getenv(argument, "PWD=")) ? dir : "/");
		else
			chdir_ret = chdir(dir);
	}
	else if (_strcmp(argument->argv[1], "-") == 0)
	{
		dir = _getenv(argument, "OLDPWD=");
		if (!dir)
		{
			_puts(curr_dir);
			_putchar('\n');
			return (1);
		}
		_puts(dir), _putchar('\n');
		chdir_ret = chdir(dir);
	}
	else
		chdir_ret = chdir(argument->argv[1]);
	if (chdir_ret == -1)
	{
		print_error(argument, "can't cd to ");
		_eputs(argument->argv[1]), _eputchar('\n');
		return (1);
	}
	else
	{
		_setenv(argument, "OLDPWD", _getenv(argument, "PWD="));
		_setenv(argument, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 * my_help - displays argumentrmation about
 * shell commands or functions
 * @argument: structure contain argumentrmation
 * Return: Always 0
*/
int my_help(struct_t *argument)
{
	char **p;

	p = argument->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*p);
	return (0);
}