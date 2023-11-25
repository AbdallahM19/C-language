#include "shell.h"

/**
 * is_chain - check if it is the chain
 * @info: first member
 * @buf: seconed member
 * @p: third member
 * Return: 0 or 1
 */
int is_chain(info_t *info, char *buf, size_t *p)
{
	size_t i = *p;

	if (buf[i] == '|' && buf[i + 1] == '|')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[i] == '&' && buf[i + 1] == '&')
	{
		buf[i] = 0;
		i++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[i] == ';')
	{
		buf[i] = 0;
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);
	*p = i;
	return (1);
}

/**
 * check_chain - check the last status
 * @info: first parameter
 * @buf: seconed parameter
 * @p: third one
 * @i: parameter number 4
 * @len: the length
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t n = *p;

	if (info->cmd_buf_type == CMD_AND)
	{
		if (info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}
	if (info->cmd_buf_type == CMD_OR)
	{
		if (!info->status)
		{
			buf[i] = 0;
			n = len;
		}
	}
	*p = n;
}

/**
 * replace_alias - change an alias
 * @info: struct
 * Return: 0 or 1
 */
int replace_alias(info_t *info)
{
	int i;
	list_t *node;
	char *ptr;

	for (i = 0; i < 10; i++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);
		free(info->argv[0]);
		ptr = _strchr(node->str, '=');
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
 * replace_vars - replaces vars
 * @info: pointer to struct
 * Return: 1 or 0
 */
int replace_vars(info_t *info)
{
	int i;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;
		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(info->status, 10, 0)));
			continue;
		}
		if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
				_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_starts_with(info->env, &info->argv[i][1], '=');
		if (node)
		{
			replace_string(&(info->argv[i]),
				_strdup(_strchr(node->str, '=') + 1));
			continue;
		}
		replace_string(&info->argv[i], _strdup(""));
	}
	return (0);
}

/**
 * replace_string - replaces string
 * @old: first member
 * @new: seconed one
 * Return: 1
*/
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}