#include "lists.h"

dlistint_t *add_dnodeint_end(dlistint_t **head, const int n)
{
	if (!head)
		return (NULL);
	dlistint_t *new = malloc(sizeof(dlistint_t)), *node;
	new->n = n;
	new->next = NULL;
	if (!*head)
	{
		new->prev = NULL;
		*head = new;
	}
	else
	{
		node = *head;
		while (node->next)
			node = node->next;
		node->next = new;
		new->prev = node;
	}
	return (new);
}