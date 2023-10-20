#include "lists.h"

/**
 * add_node - Write a function that adds a new node =
 * at the beginning of a list_t list.
 * @head: list_t
 * @str: char
 * Return: the address of the new element, or NULL if it fails
 */
list_t *add_node(list_t **head, const char *str)
{
	list_t *new;
	unsigned int l = 0;

	while (str[l])
		l++;

	new = malloc(sizeof(list_t));

	if (!new || !head)
		return (NULL);
	new->str = strdup(str);
	new->len = l;
	new->next = (*head);
	(*head) = new;
	return (*head);
}