#include "shell.h"

/**
 * str_tokn - split the string to toknizer
 * @command: string to be toknized
 * @delim: char
 * Return: the words splited
*
char **str_tokn(char *command, char *delim)
{
	int i, j, k, m, count = 0;
	char **s;

	if (command == NULL || command[0] == 0)
		return (NULL);
	for (i = 0; command[i] != '\0'; i++)
		if (!delim_check(command[i], delim) &&
			(delim_check(command[i + 1], delim) || !command[i + 1]))
			count++;
	if (count == 0)
		return (NULL);
	s = malloc((1 + count) * sizeof(char *));
	if (!s)
		return (NULL);
	for (i = 0, j = 0; j < count; j++)
	{
		while (delim_check(command[i], delim))
			i++;
		k = 0;
		while (!delim_check(command[i + k], delim) && command[i + k])
			k++;
		s[j] = malloc((k + 1) * sizeof(char));
		if (!s[j])
		{
			for (k = 0; k < j; k++)
				free(s[k]);
			free(s);
			return (NULL);
		}
		for (m = 0; m < k; m++)
			s[j][m] = command[i++];
		s[j][m] = 0;
	}
	s[j] = NULL;
	return (s);
}*/

/**
* file_mode - to execute from a file
*
*@av: argument
*
*@argument: pointer to the struct
*
*Return: which in the file
*
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
}*/

/**
 * handle_sign - handle ctrl-C
 * @sig: void integer
 * Return: void
 *
void handle_sign(int sign)
{
	(void) sign;
	exit(0);
}*/