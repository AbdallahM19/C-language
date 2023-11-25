#include "shell.h"

/**
 * my_history - print the history of used commands
 * @argument: struct contain arguments
 * Return: 0
*/
int my_history(struct_t *argument)
{
	print_list(argument->history);
	return (0);
}

/**
 * unset_alias - remove alias ( Unsets an alias )
 * @argument: first parameter struct
 * @str: seconed parameter struct
 * Return: 0 on success or 1 on error
*/
int unset_alias(struct_t *argument, char *str)
{
	char *sign = strchr(str, '=');
	int i;

	if (!sign)
		return (1);
	*sign = '\0';
	i = delete_node_at_index(&(argument->alias),
	get_node_index(argument->alias, node_starts_with(argument->alias, str, -1)));
	*sign = '=';
	return (i);
}

/**
 * set_alias - set alias to string
 * @argument: first parameter
 * @str: seconed parameter
 * Return: 0 or 1
*/
int set_alias(struct_t *argument, char *str)
{
	char *sign = strchr(str, '=');

	if (!sign)
		return (1);
	if (!*++sign)
	{
		unset_alias(argument, str);
		return (0);
	}
	unset_alias(argument, str);
	return (add_node_end(&(argument->alias), str, 0) == NULL);
}

/**
 * print_alias - print an alas string
 * @cat: the alias node
 * Return: 0 or 1
*/
int print_alias(list_t *cat)
{
	char *sign = strchr(cat->string, '=');
	char *a = cat->string;

	if (cat)
	{
		while (a <= sign)
		{
			putchar(*a);
			a++;
		}
		putchar('\'');
		puts(sign + 1);
		puts("'\n");
		return (0);
	}
	return (1);
}

/**
 * my_alias - manages shell aliases
 * @argument: struct contain arguments
 * Return: 0
*/
int my_alias(struct_t *argument)
{
	int i = 0;
	char *p = NULL;
	list_t *node_alias = NULL;

	if (argument->argc == 1)
	{
		node_alias = argument->alias;
		while (node_alias)
		{
			print_alias(node_alias);
			node_alias = node_alias->next;
		}
		return (0);
	}
	for (i = 1; argument->argv[i]; i++)
	{
		p = strchr(argument->argv[i], '=');
		if (p)
		{
			if (set_alias(argument, argument->argv[i]) != 0)
				return (1);
		}
		else
		{
			node_alias = node_starts_with(argument->alias, argument->argv[i], '=');
			if (node_alias)
				print_alias(node_alias);
			else
			{
				print_error(argument, "alias: ");
				print_error(argument, argument->argv[i]);
				print_error(argument, ": not found\n");
				return (1);
			}
		}
	}
	return (0);
}
