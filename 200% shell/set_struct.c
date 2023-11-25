#include "shell.h"
/**
 * init_argument - set a struct
 *
 * @argument: struct
 *
 * @argv: arguments
 *
 * Return: void
 */
void init_argument(struct_t *argument, char **argv)
{
int x = 0;
	argument->fname = argv[0];
	if (argument->arg)
	{
		argument->argv = str_tokn(argument->arg, " \t");
		if (!argument->argv)
		{
			argument->argv = malloc(sizeof(char *) * 2);
			if (argument->argv)
			{
				argument->argv[0] = _strdup(argument->arg);
				argument->argv[1] = NULL;
			}
		}
		for (x = 0; argument->argv && argument->argv[x]; x++)
			;
		argument->argc = x;
		new_alias(argument);
		new_vars(argument);
	}
}
/**
 * delete_argument - clear the stuct
 *
 * @argument: pointer to the struct
 *
 * Return: void
 */
void delete_argument(struct_t *argument)
{
	argument->arg = NULL;
	argument->argv = NULL;
	argument->path = NULL;
	argument->argc = 0;
}
