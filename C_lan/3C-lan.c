#include "lists.h"

dlistint_t *add_dnodeint(dlistint_t **head, const int n)
{
	if (!head)
		return (NULL);
	dlistint_t *new = malloc(sizeof(dlistint_t));
	new->n = n;
	new->prev = NULL;
	if (!*head)
	{
		*head = new;
		new->next = NULL;
	}
	else
	{
		new->next = *head;
		(*head)->prev = new;
		*head = new;
	}
	return (new);
}