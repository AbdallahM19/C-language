#include "shell.h"
/**
* file_mode - to execute from a file
*
*@av: argument
*
*@info: pointer to the struct
*
*Return: which in the file
*/
int file_mode(char **av, info_t *info)
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
				_eputchar(BUF_FLUSH);
				exit(127);
			}
			return (EXIT_FAILURE);
		}
		info->readfd = fd;
        return (EXIT_SUCCESS);
}
/**
* execute_command - to check the input
* 
* @info: the parameter & return info struct
*
* @argv: the argument vector from main()
*
* Return: 0 or 1
*/
int execute_command(info_t *info, char **argv)
{
	ssize_t r = 0;
	int x = 0;

	while (r != -1 && x != -2)
	{
		delete_info(info);
		if (interactive(info))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		r = get_input(info);
		if (r != -1)
		{
			init_info(info, argv);
			x = check_builtin(info);
			if (x == -1)
				command_placeholder(info);
		}
		else if (interactive(info))
			_putchar('\n');
		free_info(info, 0);
	}
	history_writing(info);
	free_info(info, 1);
	if (!interactive(info) && info->status)
		exit(info->status);
	if (x == -2)
	{
		if (info->err_num == -1)
			exit(info->status);
		exit(info->err_num);
	}
	return (x);
}
/**
 * check_builtin - execute the builtin command
 * 
 * @info: pointer to the struct
 *
 * Return: -1 or 0 or 1 or -2
 */
int check_builtin(info_t *info)
{
	int x, built_execut = -1;
	builtin_table builtcommand[] = {
		{"exit", _myexit},
		{"env", _myenv},
		{"help", _myhelp},
		{"history", _myhistory},
		{"setenv", _mysetenv},
		{"unsetenv", _myunsetenv},
		{"cd", _mycd},
		{"alias", _myalias},
		{NULL, NULL}
	};

	for (x = 0; builtcommand[x].type; x++)
		if (_strcmp(info->argv[0], builtcommand[x].type) == 0)
		{
			info->line_count++;
			built_execut = builtcommand[x].func(info);
			break;
		}
	return (built_execut);
}

/**
 * fork_command( - fork to execute a command
 * 
 * @info: pointer to thw struct
 *
 * Return: void
 */
void fork_command(info_t *info)
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
		if (execve(info->path, info->argv, get_environ(info)) == -1)
		{
			free_info(info, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(info->status));
		if (WIFEXITED(info->status))
		{
			info->status = WEXITSTATUS(info->status);
			if (info->status == 126)
				print_error(info, "Permission denied\n");
		}
	}
}

/**
* command_placeholder - finds a command in PATH
*
* @info: pointer to struct
*
* Return: void
*/
void command_placeholder(info_t *info)
{
	int i, k;
	char *place = NULL;
	info->path = info->argv[0];
	if (info->linecount_flag == 1)
	{
		info->line_count++;
		info->linecount_flag = 0;
	}
	for (i = 0, k = 0; info->arg[i]; i++)
		if (!is_delim(info->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	place = path_finder(info, _getenv(info, "PATH="), info->argv[0]);
	if (place)
	{
		info->path = place;
		fork_command(info);
	}
	else
	{
		if ((interactive(info) || _getenv(info, "PATH=")
			|| info->argv[0][0] == '/') && is_command(info, info->argv[0]))
			fork_command(info);
		else if (*(info->arg) != '\n')
		{
			info->status = 127;
			print_error(info, "not found\n");
		}
	}
}