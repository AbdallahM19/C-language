#include "shell.h"

/**
 * list_length - get the length of a list
 * 
 * @head: pointer to the list
 *
 * Return: the length of list
 */
size_t list_length(const list_t *head)
{
	size_t count = 0;

	while (head)
	{
		head = head->next;
		count++;
	}
	return (count);
}

/**
 * list_to_strings - convert a list to string
 * 
 * @h: pointer to the list
 *
 * Return: array
 */
char **list_to_strings(list_t *h)
{
	list_t *cat = h;
	size_t x = list_length(h), y;
	char **strs;
	char *str;

	if (!h || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; cat; cat = cat->next, x++)
	{
		str = malloc(_strlength(cat->str) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}
		str = _strcpy(str, cat->str);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}
/**
 * print_list - print the element of a list
 * 
 * @head: pointer to list
 *
 * Return: the list
 */
size_t print_list(const list_t *head)
{
	size_t count = 0;
	while (head)
	{
		_puts(convert_number(head->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->str ? head->str : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
	}
	return (count);
}

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
		p = starts_with(cat->str, pref);
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
