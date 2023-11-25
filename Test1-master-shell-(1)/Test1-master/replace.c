#include "shell.h"
/**
* new_string - replaces string
* 
* @kitty: first member
* @cat: seconed one
*
* Return: 1 
*/
int new_string(char **kitty, char *cat)
{
	free(*kitty);
	*kitty = cat;
	return (1);
}
/**
 * new_vars - replaces vars
 * @argument: pointer to struct
 *
 * Return: 1 or 0
 */
int new_vars(struct_t *argument)
{
	int x = 0;
	list_t *cat;
	for (x = 0; argument->argv[x]; x++)
	{
		if (argument->argv[x][0] != '$' || !argument->argv[x][1])
			continue;

		if (!_strcmp(argument->argv[x], "$?"))
		{
			new_string(&(argument->argv[x]),
				_strdup(convert_number(argument->status, 10, 0)));
			continue;
		}
		if (!_strcmp(argument->argv[x], "$$"))
		{
			new_string(&(argument->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		cat = node_starts_with(argument->env, &argument->argv[x][1], '=');
		if (cat)
		{
			new_string(&(argument->argv[x]),
				_strdup(_strchr(cat->string, '=') + 1));
			continue;
		}
		new_string(&argument->argv[x], _strdup(""));
	}
	return (0);
}
/**
 * new_alias - change an alias
 * @argument: struct
 *
 * Return: 0 or 1
 */
int new_alias(struct_t *argument)
{
	int x;
	char *ptr;
	list_t *cat;
	for (x = 0; x < 10; x++)
	{
		cat = node_starts_with(argument->alias, argument->argv[0], '=');
		if (!cat)
			return (0);
		free(argument->argv[0]);
		ptr = _strchr(cat->string, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		argument->argv[0] = ptr;
	}
	return (1);
}
