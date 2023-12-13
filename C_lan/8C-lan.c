#include "lists.h"

dlistint_t *insert_dnodeint_at_index(dlistint_t **h, unsigned int idx, int n)
{
	dlistint_t *tab = *h, *new;

	if (idx == 0)
		return (add_dnodeint(h, n));
	while (idx != 1)
	{
		tab = tab->next;
		if (tab == NULL)
			return (NULL);
		idx--;
	}
	if (tab->next == NULL)
		return (add_dnodeint_end(h, n));
	new = malloc(sizeof(dlistint_t));
	if (new == NULL)
		return (NULL);
	new->n = n;
	new->prev = tab;
	new->next = tab->next;
	tab->next->prev = new;
	tab->next = new;
	return(new);
}