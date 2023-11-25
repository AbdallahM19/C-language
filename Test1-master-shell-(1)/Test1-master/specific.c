#include "shell.h"
/**
 * node_starts_with - get a node
 * 
 * @cat: pointer to the list
 * 
 * @pref: string
 * 
 * @ch: char
 *
 * Return: match node or null
 */
list_t *node_starts_with(list_t *cat, char *pref, char ch)
{
	char *p = NULL;

	while (cat)
	{
		p = starts_with(cat->string, pref);
		if (p && ((ch == -1) || (*p == ch)))
			return (cat);
		cat = cat->next;
	}
	return (NULL);
}
/**
 * get_node_index - get an index
 * 
 * @head: first member
 * 
 * @cat: seconed
 *
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *cat)
{
	size_t index = 0;

	while (head)
	{
		if (head == cat)
			return (index);
		head = head->next;
		index++;
	}
	return (-1);
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
		free(cat->string);
		free(cat);
		return (1);
	}
	cat = *h;
	while (cat)
	{
		if (i == index)
		{
			prev_cat->next = cat->next;
			free(cat->string);
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
*_strchr - find specific characther in string
*
*@p: the string
*
*@x: the char
*
*Return: the pointer or NULL
*/
char *_strchr(char *p, char x)
{
	while (*p != '\0')
	{
		if (*p == x)
			return (p);
		p++;
	}
	return (NULL);
}