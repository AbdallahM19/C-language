#include "lists.h"

dlistint_t *get_dnodeint_at_index(dlistint_t *head, unsigned int index)
{
	for (unsigned int i = 0; head; i++)
	{
		if (i == index)
			return (head);
		head = head->next;
	}
	return (NULL);
}