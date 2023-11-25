#include "shell.h"

/**
 * _myenv - prints the new environment
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: environment variable name
 * Return: the value
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;

	while (node != NULL)
	{
		char *p = starts_with(node->str, name);

		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - Initialize a new environment variable,
 * or modify an existing one
 * @info: structure containing potential arguments,
 * Used to maintain constant function prototype.
 * Return: O, 1 if error
 */
int _mysetenv(info_t *info)
{
	char *a = info->argv[1];
	char *b = info->argv[2];

	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, a, b) != 0)
	{
		_eputs("Failed to update environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * _myunsetenv - Remove an environmental variable.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int i;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= info->argc; i++)
	{
		if (_unsetenv(info, info->argv[i]) != 0)
		{
			_eputs("Failed to remove environment variable.\n");
			return (1);
		}
	}
	return (0);
}

/**
 * populate_env_list - populates env linked list.
 * @info: structure containing potential arguments.
 * used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&(node), environ[i], 0);
	info->env = node;
	return (0);
}