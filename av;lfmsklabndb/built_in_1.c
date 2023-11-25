#include "shell.h"

/**
 * _myhistory - print the history of used commands
 * @info: struct contain arguments
 * Return: 0
*/
int _myhistory(info_t *info)
{
	print_list(info->history);
	return (0);
}

/**
 * unset_alias - remove alias ( Unsets an alias )
 * @info: first parameter struct
 * @str: seconed parameter struct
 * Return: 0 on success or 1 on error
*/
int unset_alias(info_t *info, char *str)
{
	char *sign = _strchr(str, '='), c;
	int i;

	if (!sign)
		return (1);
	c = *sign;
	*sign = 0;
	i = delete_node_at_index(&(info->alias),
	get_node_index(info->alias, node_starts_with(info->alias, str, -1)));
	*sign = c;
	return (i);
}

/**
 * set_alias - set alias to string
 * @info: first parameter
 * @str: seconed parameter
 * Return: 0 or 1
*/
int set_alias(info_t *info, char *str)
{
	char *sign = _strchr(str, '=');

	if (!sign)
		return (1);
	if (!*++sign)
		return (unset_alias(info, str));

	unset_alias(info, str);
	return (add_node_end(&(info->alias), str, 0) == NULL);
}

/**
 * print_alias - print an alas string
 * @node: the alias node
 * Return: 0 or 1
*/
int print_alias(list_t *node)
{
	char *sign = NULL, *a = NULL;

	if (node)
	{
		sign = _strchr(node->str, '=');
		for (a = node->str; a <= sign; a++)
			_putchar(*a);
		_putchar('\'');
		_puts(sign + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * _myalias - manages shell aliases
 * @info: struct contain arguments
 * Return: 0
*/
int _myalias(info_t *info)
{
	int i = 0;
	char *sign = NULL;
	list_t *node = NULL;

	if (info->argc == 1)
	{
		node = info->alias;
		while (node)
		{
			print_alias(node);
			node = node->next;
		}
		return (0);
	}
	i = 1;
	while (info->argv[i])
	{
		sign = _strchr(info->argv[i], '=');
		if (sign)
			set_alias(info, info->argv[i]);
		else
			print_alias(node_starts_with(info->alias, info->argv[i], '='));
		i++;
	}
	return (0);
}