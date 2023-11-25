#include "shell.h"

/**
 * is_non_interactive - Run the shell in non-interactive mode
 * @name: Name of the shell executable
 */
void is_non_interactive(char *name)
{
	int s = 0, i = 1;
	char *buf = NULL, **arr = NULL;
	size_t st = 0;

	while (_getline(&buf, &st, STDIN_FILENO, 1) != -1)
	{
		remove_comments(buf);
		arr = make_array_str(buf, " \n\t");
		arr = replace_var(arr, s);
		if (search_in_implem(arr, &s, i, name))
		{
			if (arr[0] && access(arr[0], F_OK | X_OK) == 0)
				execute_command(arr[0], arr, &s);
			else if (!arr[0])
				{}
			else
			{
				char *command = search_in_command(arr[0]);
				if (!command)
				{
					show_error(name, i, arr[0], "not found\n");
					s = 127;
				}
				else
					execute_command(command, arr, &s);
				free(command);
			}
		}
		free_array(arr);
		++i;
	}
	is_exit(NULL, s, i, name);
	free(buf);
}