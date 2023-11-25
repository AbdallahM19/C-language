#include "shell.h"
/**
 * init_info - set info_t struct
 * 
 * @info: struct 
 * 
 * @av: arguments
 * 
 * Return: void
 */
void init_info(info_t *info, char **argv)
{
	int x = 0;
	info->fname = argv[0];
	if (info->arg)
	{
		info->argv = str_tokn(info->arg, " \t");
		if (!info->argv)
		{
			info->argv = malloc(sizeof(char *) * 2);
			if (info->argv)
			{
				info->argv[0] = _strdup(info->arg);
				info->argv[1] = NULL;
			}
		}
		for (x = 0; info->argv && info->argv[x]; x++)
			;
		info->argc = x;
		new_alias(info);
		new_vars(info);
	}
}
/**
 * delete_info - clear the stuct
 * 
 * @info: pointer to the struct
 * 
 * Return: void
 */
void delete_info(info_t *info)
{
	info->arg = NULL;
	info->argv = NULL;
	info->path = NULL;
	info->argc = 0;
}
/**
 * free_info - free a struct
 * 
 * @info: pointer to the stuct
 * 
 * @dl: int to check
 * 
 * Return: void
 */
void free_info(info_t *info, int dl)
{
	free_string(info->argv);
	info->argv = NULL;
	info->path = NULL;
	if (dl)
	{
		if (!info->cmd_buf)
			free(info->arg);
		if (info->env)
			list_free(&(info->env));
		if (info->history)
			list_free(&(info->history));
		if (info->alias)
			list_free(&(info->alias));
		free_string(info->environ);
			info->environ = NULL;
		free_pointer((void **)info->cmd_buf);
		if (info->readfd > 2)
			close(info->readfd);
		_putchar(BUF_FLUSH);
	}
}
