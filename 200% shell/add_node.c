#include "shell.h"

/**
 * add_node_head - add new node to the head
 * @head: pfirst member
 * @string: seconed one
 * @n: third one
 * Return: size of list
 */
list_t *add_node_head(list_t **head, const char *string, int n)
{
	list_t *new;
	

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	memset((void *)new, 0, sizeof(list_t));
	new->n = n;
	if (string)
	{
		new->string = _strdup(string);
		if (!new->string)
		{
			free(new);
			return (NULL);
		}
	}
	new->next = *head;
	*head = new;
	return (new);
}

/**
 * add_node_end - add b=node to the tail
 * @head: pfirst member
 * @string: seconed one
 * @n: third one
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *string, int n)
{
	list_t *new_cat, *cat;
	
	if (!head)
		return (NULL);

	new_cat = malloc(sizeof(list_t));
	if (!new_cat)
		return (NULL);

	memset((void *)new_cat, 0, sizeof(list_t));
	new_cat->n = n;
	if (string)
	{
		new_cat->string = _strdup(string);
		if (!new_cat->string)
		{
			free(new_cat);
			return (NULL);
		}
	}
	new_cat->next = NULL;
	if (*head)
	{
		cat = *head;
		while (cat->next)
			cat = cat->next;
		cat->next = new_cat;
	}
	else
		*head = new_cat;
	return (new_cat);
}