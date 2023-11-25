#include "shell.h"

/**
 * list_len - get the length of a list
 * @h: pointer to the list
 * Return: the length of list
*/
size_t list_len(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
		h = h->next;
	return (i);
}

/**
 * list_to_strings - convert a list to string
 * @head: pointer to the list
 * Return: array
 */
char **list_to_strings(list_t *head)
{
	list_t *node = head;
	size_t i = list_len(head), n;
	char **strs;
	char *str;

	if (!head || !i)
		return (NULL);
	strs = malloc(sizeof(char *) * (i + 1));
	if (!strs)
		return (NULL);
	for (i = 0; node; node = node->next, i++)
	{
		str = malloc(_strlen(node->str) + 1);
		if (!str)
		{
			for (n = 0; n < i; n++)
				free(strs[n]);
			free(strs);
			return (NULL);
		}

		str = _strcpy(str, node->str);
		strs[i] = str;
	}
	strs[i] = NULL;
	return (strs);
}


/**
 * print_list - print the element of a list
 * @h: pointer to list
 * Return: the list
 */
size_t print_list(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
	}
	return (i);
}

/**
 * node_starts_with - get a node
 * @node: pointer to the list
 * @prefix: string
 * @c: char
 * Return: match node or null
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *ptr = NULL;

	while (node)
	{
		ptr = starts_with(node->str, prefix);
		if (ptr && ((c == -1) || (*ptr == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - get an index
 * @head: first member
 * @node: seconed
 * Return: index of node or -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t i;

	for (i = 0; head; i++)
	{
		if (head == node)
			return (i);
		head = head->next;
	}
	return (-1);
}