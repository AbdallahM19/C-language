list_t *add_node_end(list_t **head, const char *string, int n)
{
	list_t *new_node, *last_node;

	if (!head || !*head)
		return (NULL);

	new_node = malloc(sizeof(list_t));
	if (!new_node)
		return (NULL);

	memset((void *)new_node, 0, sizeof(list_t));
	new_node->n = n;

	if (string)
	{
		new_node->string = _strdup(string);
		if (!new_node->string)
		{
			free(new_node);
			return (NULL);
		}
	}
	else
	{
		new_node->string = NULL;
	}
	new_node->next = NULL;
	if (*head)
	{
		last_node = *head;
		while (last_node->next)
			last_node = last_node->next;

		last_node->next = new_node;
	}
	else
	{
		*head = new_node;
	}
	return (new_node);
}