#include "lists.h"

/**
 * list_len - calculates the sum of elements in a linked list of integers
 * @h: pointer to the first node in the list
 * Return: the sum of elements in the list
 */
size_t list_len(const list_t *h)
{
	int sum = 0;

	while (h)
	{
		sum++;
		h = h->next;
	}
	return (sum);
}