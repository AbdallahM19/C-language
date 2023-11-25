#include "shell.h"

/**
 * bfree - free pointeres
 * @str: pointer
 * Return: 1 or 0
 */
int bfree(void **str)
{
	if (str && *str)
	{
		free(*str);
		*str = NULL;
		return (1);
	}
	return (0);
}