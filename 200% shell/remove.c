#include "shell.h"

/**
 * remove_comments - removecoments
 * @str: pointer
 * Return: Always 0;
 */
void remove_comments(char *str)
{
	int i = 0;

	if (!(str))
		return;
	while ((str)[i] != '\0')
	{
		if ((str)[i] == '#')
		{
			if (i == 0 || (str)[i - 1] == ' ')
			{
				(str)[i] = '\0';
				break;
			}
		}
		i++;
	}
}