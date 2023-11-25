#include "shell.h"

/**
 * add_node - add new node to the head
 * @head: pfirst member
 * @str: seconed one
 * @num: third one
 * Return: size of list
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *new;

	if (!head)
		return (NULL);
	new = malloc(sizeof(list_t));
	if (!new)
		return (NULL);
	_memset((void *)new, 0, sizeof(list_t));
	new->num = num;
	if (str)
	{
		new->str = _strdup(str);
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
 * @head: pfirst member
 * @str: seconed one
 * @num: third one
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *node, *new_node;

	if (!head)
		return (NULL);

	node = *head;
	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);
	_memset((void *)new_node, 0, sizeof(list_t));
	new_node->num = num;
	if (str)
	{
		new_node->str = _strdup(str);
		if (!new_node->str)
		{
			free(new_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = new_node;
	}
	else
		*head = new_node;
	return (new_node);
}

/**
 * print_list_str - print specific element
 * @h: pointer to first node
 * Return: the list
 */
size_t print_list_str(const list_t *h)
{
	size_t i;

	for (i = 0; h; i++)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
	}
	return (i);
}

/**
 * delete_node_at_index - delete specific node
 * @head: pointer of pointer
 * @index: index of node to delete
 * Return: 1 on success, 0 on failure
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int i = 0;

	if (!head || !*head)
		return (0);
	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->str);
		free(node);
		return (1);
	}
	for (node = *head; node; i++)
	{
		if (i == index)
		{
			prev_node->next = node->next;
			free(node->str);
			free(node);
			return (1);
		}
		prev_node = node;
		node = node->next;
	}
	return (0);
}

/**
 * free_list - free the nodes of list
 * @head_ptr: pointer to list
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->str);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}