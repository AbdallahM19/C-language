#include"shell.h"

/**
 * list_to_strings - convert linked list to array of strings in a specific order
 * @head: pointer to the struct
 * Return: array of strings
 */
char **list_to_strings(list_t *info)
{
	const char *desired_order[] = {
		"LESSOPEN=",
		"LANGUAGE=",
		"HOSTNAME=",
		"SHLVL=",
		"HOME=",
		"OLDPWD=",
		"TZ=",
		NULL
	};

	char **strs;
	size_t i, j;

	strs = malloc(sizeof(char *) * (list_length(info->env) + 1));

	if (!strs)
		return (NULL);

	for (i = 0; desired_order[i] != NULL; i++)
	{
		list_t *node = info->env;
		while (node != NULL)
		{
			char *p = starts_with(node->str, desired_order[i]);

			if (p && *p)
			{
				strs[i] = malloc(_strlength(node->str) + 1);
				if (!strs[i])
				{
					for (j = 0; j < i; j++)
						free(strs[j]);
					free(strs);
					return NULL;
				}
				strs[i] = _strcpy(strs[i], node->str);
				break;
			}
			node = node->next;
		}
		if (desired_order[i] != NULL && node == NULL)
		{
			strs[i] = malloc(1);
			if (!strs[i])
			{
				for (j = 0; j < i; j++)
					free(strs[j]);
				free(strs);
				return NULL;
			}
			strs[i][0] = '\0';
		}
	}
	strs[i] = NULL;
	return (strs);
}