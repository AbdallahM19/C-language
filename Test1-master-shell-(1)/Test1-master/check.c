#include "shell.h"

/**
 * delim_check - checks if character is a delimeter
 * @c: first member
 * @d: secooned one
 * Return: 1 or 0
*/
int delim_check(char c, char *d)
{
	while (*d)
		if (*d++ == c)
			return (1);
	return (0);
}

/**
 *alpha_check- test if it is char
 *@s: a char
 *Return: 1 or 0
*/
int alpha_check(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * is_command - check if it is command
 * @argument: pointer to struct
 * @place: the path
 * Return: 1 if true, 0 otherwise
 */
int is_command(struct_t *argument, char *place)
{
	struct stat ls;
	(void)argument;
	if (!place || stat(place, &ls))
		return (0);

	if (ls.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * starts_with - checks if specific word start with specific char
 * @cat: first member
 * @kitty: seconed one
 * Return: pointer
*/
char *starts_with(const char *cat, const char *kitty)
{
    while (*kitty) {
        if (*kitty != *cat)
            return NULL;
        kitty++;
        cat++;
    }
    return ((char *)cat);
}

/**
 * check_builtin - execute the builtin command
 * @argument: pointer to the struct
 * Return: -1 or 0 or 1 or -2
 */
int check_builtin(struct_t *argument)
{
	int x, built_execut = -1;
	builtin_command builtcommand[] = {
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

	for (x = 0; builtcommand[x].name; x++)
		if (_strcmp(argument->argv[0], builtcommand[x].name) == 0)
		{
			argument->line_count++;
			built_execut = builtcommand[x].job(argument);
			break;
		}
	return (built_execut);
}