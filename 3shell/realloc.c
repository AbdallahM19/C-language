#include "shell.h"
/**
*_memset - fills memory with a constant byte
*
*@s: pointer to the area we will fill
*
*@b: char contain the data
*
*@n: uninsigned int to start with
*
*Return: (*S)
*/
char *_memset(char *s, char b, unsigned int n)
{
int i = 0;
	while (n > 0)
{
	s[i] = b;
	i++;
	n--;
}
	return (s);
}
/**
 * free_string - free memory
 * 
 * @ptr: pointer to the string
 * 
 * Return: void
 */
void free_string(char **ptr)
{
	char **s = ptr;

	if (!ptr)
		return;
	while (*ptr)
		free(*ptr++);
	free(s);
}
/**
*_realloc - reallocates a memory block using malloc and free
*
*@ptr: pointer
*
*@old_size: the size we will change
*
*@new_size: the new size
*
*Return: (ptr or NULL)
*/
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
void *rptr;
	if (new_size == old_size)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new_size));
	if (new_size == 0 && ptr != NULL)
{
		free(ptr);
		return (NULL);
}
rptr = malloc(new_size);
	if (new_size > old_size)
		memcpy(rptr, ptr, old_size);
	else
		memcpy(rptr, ptr, new_size);
	free(ptr);
	return (rptr);
}
