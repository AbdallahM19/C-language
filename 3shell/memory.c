#include "shell.h"

/**
 * free_pointer - free  pointeres
 * 
 * @cat: pointer
 *
 * Return: 1 or 0
 */
int free_pointer(void **cat)
{
	if (cat && *cat)
	{
		free(*cat);
		*cat = NULL;
		return (1);
	}
	return (0);
}
