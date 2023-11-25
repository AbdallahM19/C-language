#include "shell.h"
/**
 * free_pointer - free pointeres
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
/**
 * list_free - free the nodes of list
 * 
 * @ptr: pointer to list
 *
 * Return: void
 */
void list_free(list_t **ptr)
{
	list_t *cat, *next_node, *head;

	if (!ptr || !*ptr)
		return;
	head = *ptr;
	cat = head;
	while (cat)
	{
		next_node = cat->next;
		free(cat->string);
		free(cat);
		cat = next_node;
	}
	*ptr = NULL;
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
 * free_argument - free a struct
 * 
 * @argument: pointer to the stuct
 * 
 * @dl: int to check
 * 
 * Return: void
 */
void free_argument(struct_t *argument, int dl)
{
	free_string(argument->argv);
	argument->argv = NULL;
	argument->path = NULL;
	if (dl)
	{
		if (!argument->cmd_buf)
			free(argument->arg);
		if (argument->env)
			list_free(&(argument->env));
		if (argument->history)
			list_free(&(argument->history));
		if (argument->alias)
			list_free(&(argument->alias));
		free_string(argument->environ);
			argument->environ = NULL;
		free_pointer((void **)argument->cmd_buf);
		if (argument->readfd > 2)
			close(argument->readfd);
		_putchar(NEGATTIVE);
	}
}
