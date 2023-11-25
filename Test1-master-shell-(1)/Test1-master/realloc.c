#include "shell.h"
/**
*_realloc - reallocates a memory block using malloc and free
*
*@ptr: pointer
*
*@old: the size we will change
*
*@new: the new size
*
*Return: (ptr or NULL)
*/
void *_realloc(void *ptr, unsigned int old, unsigned int new)
{
void *rptr;
	if (new == old)
		return (ptr);
	if (ptr == NULL)
		return (malloc(new));
	if (new == 0 && ptr != NULL)
{
		free(ptr);
		return (NULL);
}
rptr = malloc(new);
	if (new > old)
		memcpy(rptr, ptr, old);
	else
		memcpy(rptr, ptr, new);
	free(ptr);
	return (rptr);
}
