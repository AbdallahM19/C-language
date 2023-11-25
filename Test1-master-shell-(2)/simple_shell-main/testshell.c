#include "shell.h"

/**
 * replace_alias - change an alias
 * @info: struct
 * Return: 0 or 1
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	while (i < 10)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
		i++;
	}
	return (1);
}