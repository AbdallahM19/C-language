#include "shell.h"

/**
 * is_interactive - shell interactive
 * @name: char
 * Return: command
*/
void is_interactive(char *name)
{
	int i = 1, s = 0;
	char *prompt = "$ ", *buf = NULL, *command = NULL, **arr = NULL;
	size_t st = 0;

	while (1)
	{
		buf = NULL, command = NULL, arr = NULL, st = 0;
		write(1, prompt, 2);
		if (_getline(&buf, &st, STDIN_FILENO, 1) == -1)
			free(buf), exit(0);
		remove_comments(buf);
		arr = make_array_str(buf, " \n\t");
		arr = replace_var(arr, s);
		free(buf);
		if (search_in_implem(arr, &s, i, name))
		{
			if (arr[0] && access(arr[0], F_OK | X_OK) == 0)
				execute_command(arr[0], arr, &s);
			else if (!arr[0])
				{}
			else
			{
				command = search_in_command(arr[0]);
				if (!command)
				{
					show_error(name, i, arr[0], "not found\n");
					s = 127;
				}
				else
					execute_command(command, arr, &s);
			}
			free(command);
		}
		free_array(arr);
		++i;
	}
	is_exit(NULL, s, i, name);
}