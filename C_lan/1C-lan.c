#include "lists.h"

size_t dlistint_len(const dlistint_t *h)
{
	for (size_t i = 0; h; i++)
	{
		printf("%d\n", h->n);
		h = h->next;
	}
	return (i);
}