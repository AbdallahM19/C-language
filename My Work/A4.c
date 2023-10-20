#include "lists.h"

/**
 * add_node_end - Write a function that adds a new node
 * at the end of a list_t list.
 * @head: list_t
 * @str: char
 * Return: the address of the new element, or NULL if it failed
 */
list_t *add_node_end(list_t **head, const char *str)
{
	list_t *new;
	list_t *current = *head;
	unsigned int l = 0;

	while (str[l])
		l++;
	new = malloc(sizeof(list_t));
	if (!new || !head)
		return (NULL);
	new->str = strdup(str);
	new->len = l;
	new->next = NULL;
	if (*head == NULL)
	{
		*head = new;
		return (new);
	}
	while (current->next)
		current = current->next;
	current->next = new;
	return (new);
}