#include "shell.h"

/**
 * delim_check - checks if character is a delimeter
 * @c: first member
 * @d: secooned one
 * Return: 1 or 0
*/
int delim_check(char c, char *delim)
{
	while (*delim != '\0')
	{
		if (c == *delim)
			return (1);
		delim++;
	}
	return (0);
}