#include "shell.h"

/**
 * my_env - prints the new environment
 * @argument: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0
 */
int my_env(struct_t *argument)
{
	print_list_str(argument->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @argument: Structure containing potential arguments
 * @name: environment variable name
 * Return: the value
*/
char *get_env(struct_t *argument, const char *name)
{
	list_t *cat = argument->env;
	while (cat != NULL)
	{
		char *p = starts_with(cat->string, name);

		if (p && *p)
			return (p);
		cat = cat->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initialize a new environment variable,
 * or modify an existing one
 * @argument: structure containing potential arguments,
 * Used to maintain constant function prototype.
 * Return: O, 1 if error
 */
int my_setenv(struct_t *argument)
{
	char *a = argument->argv[1];
	char *b = argument->argv[2];

	if (argument->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(argument, a, b) != 0)
	{
		_eputs("Failed to update environment variable\n");
		return (1);
	}
	return (0);
}

/**
 * my_unsetenv - Remove an environmental variable.
 * @argument: Structure containing potential arguments.
 * Used to maintain constant function prototype.
 * Return: Always 0.
 */
int my_unsetenv(struct_t *argument)
{
	int i;

	if (argument->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (i = 1; i <= argument->argc; i++)
	{
		if (_unsetenv(argument, argument->argv[i]) != 0)
		{
			_eputs("Failed to remove environment variable.\n");
			return (1);
		}
	}
	return (0);
}

/**
 * populate_env_list - populates env linked list.
 * @argument: structure containing potential arguments.
 * used to maintain constant function prototype.
 * Return: Always 0
 */
int populate_env_list(struct_t *argument)
{
	list_t *node = NULL;
	size_t i;

	for (i = 0; environ[i]; i++)
		add_node_end(&(node), environ[i], 0);
	argument->env = node;
	return (0);
}