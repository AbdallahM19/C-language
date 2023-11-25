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
 * new_alias - change an alias
 * @info: struct
 *
 * Return: 0 or 1
 */
int new_alias(info_t *info)
{
	int x;
	char *ptr;
	list_t *cat;
	for (x = 0; x < 10; x++)
	{
		cat = node_starts_with(info->alias, info->argv[0], '=');
		if (!cat)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(cat->str, '=');
		if (!ptr)
			return (0);
		ptr = _strdup(ptr + 1);
		if (!ptr)
			return (0);
		info->argv[0] = ptr;
	}
	return (1);
}
/**
 * new_vars - replaces vars 
 * 
 * @info: pointer to struct
 *
 * Return: 1 or 0
 */
int new_vars(info_t *info)
{
	int x = 0;
	list_t *cat;
	for (x = 0; info->argv[x]; x++)
	{
		if (info->argv[x][0] != '$' || !info->argv[x][1])
			continue;

		if (!_strcmp(info->argv[x], "$?"))
		{
			new_string(&(info->argv[x]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[x], "$$"))
		{
			new_string(&(info->argv[x]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		cat = node_starts_with(info->env, &info->argv[x][1], '=');
		if (cat)
		{
			new_string(&(info->argv[x]),
				_strdup(_strchr(cat->str, '=') + 1));
			continue;
		}
		new_string(&info->argv[x], _strdup(""));
	}
	return (0);
}

/**
 * is_chain - check if it is the chain
 * 
 * @info: first member
 * 
 * @cat: seconed member
 * 
 * @ptr: third member
 *
 * Return: 0 or 1
 */
int is_chain(info_t *info, char *cat, size_t *ptr)
{
	size_t i = *ptr;
	if (cat[i] == '|' && cat[i + 1] == '|')
	{
		cat[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (cat[i] == '&' && cat[i + 1] == '&')
	{
		cat[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (cat[i] == ';')
	{
		cat[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*ptr = i;
	return (1);
}
/**
 * check_chain - check the last status
 * 
 * @info: first parameter
 * @cat: seconed parameter
 * @ptr: third one
 * @x: parameter number 4
 * @length: the length
 *
 * Return: Void
 */
void check_chain(info_t *info, char *cat, size_t *ptr, size_t x, size_t length)
{
	size_t y = *ptr;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			cat[x] = 0;
			y = length;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			cat[x] = 0;
			y = length;
		}
	}
	*ptr = y;
}

