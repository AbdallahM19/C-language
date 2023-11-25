#include "shell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: pointer to the area we will fill
 * @b: char contain the data
 * @n: uninsigned int to start with
 * Return: (*S)
*/
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int i = 0;

	while (i < n)
	{
		s[i] = b;
		i++;
	}
	return (s);
}

/**
 * ffree - free memory
 * @pp: pointer to the string
 * Return: void
 */
void ffree(char **pp)
{
	char **p = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(p);
}

/**
 * _realloc - reallocates a memory block using malloc and free
 * @ptr: pointer
 * @old_size: the size we will change
 * @new_size: the new size
 * Return: (ptr or NULL)
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *str;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);
	str = malloc(new_size);
	if (!str)
		return (NULL);
	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		str[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (str);
}