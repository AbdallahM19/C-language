#include"shell.h"

/**
 * get_environ - returns the string array copy of our environ
 * @argument: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
char **get_environ(struct_t *argument)
{
	if (!argument->environ || argument->env_changed)
	{
		argument->environ = list_to_strings(argument->env);
		argument->env_changed = 0;
	}
	return (argument->environ);
}

/**
 * _setenv - Initialize a few environment variable
 * or modify an existing one
 * @argument: Structure containing potential arguments.
 * @var: the string env var property
 * @value: the string env var value
 * Return: Always 0
*/
int _setenv(struct_t *argument, char *var, char *value)
{
	char *buf = NULL;
	list_t *cat;
	char *a;

	if (!var || !value)
		return (1);

	buf = malloc(_strlength(var) + _strlength(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	cat = argument->env;
	while (cat)
	{
		a = starts_with(cat->string, var);
		if (a && *a == '=')
		{
			free(cat->string);
			cat->string = buf;
			argument->env_changed = 1;
			return (0);
		}
		cat = cat->next;
	}
	if (add_node_end(&(argument->env), buf, 0) == NULL)
	{
		free(buf);
		return (1);
	}
	argument->env_changed = 1;
	return (0);
}
/**
 * _unsetenv - Remove an environment variable
 * @argument: structure containing potential arguments.
 * @var: the string env var property
 * Return: 1 on delete, 0 otherwise
 */
int _unsetenv(struct_t *argument, char *var)
{
	list_t *node = argument->env;
	size_t i = 0;
	char *a;

	if (!node || !var)
		return (0);
	while (node)
	{
		a = starts_with(node->string, var);
		if (a && *a == '=')
		{
			argument->env_changed = delete_node_at_index(&(argument->env), i);
			i = 0;
			node = argument->env;
			continue;
		}
		node = node->next;
		i++;
	}
	return (argument->env_changed);
}
