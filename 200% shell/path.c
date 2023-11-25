#include "shell.h"
/**
* command_placeholder - finds a command in PATH
*
* @argument: pointer to struct
*
* Return: void
*/
void command_placeholder(struct_t *argument)
{
int i, k;
char *place = NULL;
	argument->path = argument->argv[0];
	if (argument->linecount_flag == 1)
	{
		argument->line_count++;
		argument->linecount_flag = 0;
	}
	for (i = 0, k = 0; argument->arg[i]; i++)
		if (!delim_check(argument->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	place = path_finder(argument, get_env(argument, "PATH="), argument->argv[0]);
	if (place)
	{
		argument->path = place;
		fork_command(argument);
	}
	else
	{
		if ((interactive_mode(argument) || get_env(argument, "PATH=")
			|| argument->argv[0][0] == '/') && is_command(argument, argument->argv[0]))
			fork_command(argument);
		else if (*(argument->arg) != '\n')
		{
			argument->status = 127;
			print_error(argument, "not found\n");
		}
	}
}
/**
 * path_finder - find the path
 *
 * @argument: struct
 *
 * @place: string
 *
 * @commandd: commandd to find the path
 *
 * Return: full path
 */
char *path_finder(struct_t *argument, char *place, char *commandd)
{
int i = 0, p = 0;
char *path;
	if (!place)
		return (NULL);
	if ((_strlength(commandd) > 2) && starts_with(commandd, "./"))
	{
		if (is_command(argument, commandd))
			return (commandd);
	}
	while (1)
	{
		if (!place[i] || place[i] == ':')
		{
			path = char_duplicate(place, p, i);
			if (!*path)
				_strcat(path, commandd);
			else
			{
				_strcat(path, "/");
				_strcat(path, commandd);
			}
			if (is_command(argument, path))
				return (path);
			if (!place[i])
				break;
			p = i;
		}
		i++;
	}
	return (NULL);
}
