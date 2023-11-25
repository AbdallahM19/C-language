#include "shell.h"

/**
 * start_history - get file of history
 * @argument: pointer to the struct
 * Return: pointer
 */
char *start_history(struct_t *argument)
{
	char *buffer, *x, *but;

	x = get_env(argument, "HOME=");
	if (!x)
		return (NULL);
	
	buffer = malloc(sizeof(char) * (_strlength(x) + _strlength(HIST_FILE) + 2));
	if (!buffer)
	{
		free(x);
		return (NULL);
	}
	buffer[0] = '\0';
	_strcpy(buffer, x);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	free(x);
	but = _strdup(buffer);
	free(buffer);
	return (but);
}