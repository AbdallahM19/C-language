#include "shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - Remove an environment variable
 * @info: structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t i;
	char *s;

	if (!node || !var)
		return (0);
	for (i = 0; node; i++)
	{
		s = starts_with(node->str, var);
		if (s && *s == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), i);
			i = 0;
			node = info->env;
			continue;
		}
		node = node->next;
	}
	return (info->env_changed);
}

/**
 * _setenv - Initialize a few environment variable
 * or modify an existing one
 * @info: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
*/
int _setenv(info_t *info, char *var, char *value)
{
	char *buffer = NULL;
	list_t *node;
	char *str;

	if (!var || !value)
		return (0);

	buffer = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buffer)
		return (1);
	_strcpy(buffer, var);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	node = info->env;
	while (node)
	{
		str = starts_with(node->str, var);
		if (str && *str == '=')
		{
			free(node->str);
			node->str = buffer;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), buffer, 0);
	free(buffer);
	info->env_changed = 1;
	return (0);
}