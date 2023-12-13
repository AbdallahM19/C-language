#include "lists.h"

size_t dlistint_len(const dlistint *h)
{
    for (size_t i = 0; h; i++)
        h = h->next;
    return (i);
}