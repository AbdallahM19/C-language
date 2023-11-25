#include "shell.h"
/**
 * add_node_head - add new node to the head
 * 
 * @head: pfirst member
 * 
 * @string: seconed one
 * 
 * @n: third one
 *
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
	_memset((void *)new, 0, sizeof(list_t));
	new->num = n;
	if (string)
	{
		new->str = _strdup(string);
		if (!new->str)
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
 * 
 * @head: pfirst member
 * 
 * @string: seconed one
 * 
 * @n: third one
 *
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *string, int n)
{
	list_t *new_cat, *cat;
	if (!head)
		return (NULL);
	cat = *head;
	new_cat = malloc(sizeof(list_t));
	if (!new_cat)
		return (NULL);
	_memset((void *)new_cat, 0, sizeof(list_t));
	new_cat->num = n;
	if (string)
	{
		new_cat->str = _strdup(string);
		if (!new_cat->str)
		{
			free(new_cat);
			return (NULL);
		}
	}
	if (cat)
	{
		while (cat->next)
			cat = cat->next;
		cat->next = new_cat;
	}
	else
		*head = new_cat;
	return (new_cat);
}
/**
 * print_list_str - print specific element
 * 
 * @head: pointer to first node
 *
 * Return: the list
 */
size_t print_list_str(const list_t *head)
{
	size_t x = 0;
	while (head)
	{
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}
/**
 * delete_node_at_index - delete specific node
 * 
 * @h: pointer of pointer
 * 
 * @index: index of node to delete
 *
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **h, unsigned int index)
{
	list_t *cat, *prev_cat;
	unsigned int i = 0;

	if (!h || !*h)
		return (0);

	if (!index)
	{
		cat = *h;
		*h = (*h)->next;
		free(cat->str);
		free(cat);
		return (1);
	}
	cat = *h;
	while (cat)
	{
		if (i == index)
		{
			prev_cat->next = cat->next;
			free(cat->str);
			free(cat);
			return (1);
		}
		i++;
		prev_cat = cat;
		cat = cat->next;
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
		free(cat->str);
		free(cat);
		cat = next_node;
	}
	*ptr = NULL;
}
