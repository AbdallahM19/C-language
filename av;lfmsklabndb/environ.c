#include "shell.h"

/**
 * _myenv - prints the new environment
 * @info: structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int _myenv(info_t *info)
{
	print_list_str(info->env), return (0);
}

/**
 * _getenv - gets the value of an environ variable
 * @info: Structure containing potential arguments
 * @name: environment variable name
 * Return: the value str if not return null
*/
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *str;

	while (node)
	{
		str = starts_with(node->str, name);
		if (str && *str)
			return (str);
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
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Remove an environmental variable.
 * @info: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0.
 */
int _myunsetenv(info_t *info)
{
	int i = 1;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	while (i <= info->argc)
	{
		_unsetenv(info, info->argv[i]);
		i++;
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
	size_t i = 0;

	while (environ[i])
	{
		add_node_end(&node, environ[i], 0);
		i++;
	}
	info->env = node;
	return (0);
}