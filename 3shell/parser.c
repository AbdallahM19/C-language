#include "shell.h"
/**
 * is_command - check if it is command
 * 
 * @info: pointer to struct
 * 
 * @place: the path
 *
 * Return: 1 if true, 0 otherwise
 */
int is_command(info_t *info, char *place)
{
	struct stat ls;
	(void)info;
	if (!place || stat(place, &ls))
		return (0);

	if (ls.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}
/**
 * char_duplicate - dublicate a char
 * 
 * @place: path
 * 
 * @x: start
 * 
 * @y: stop
 *
 * Return: pointer to new buffer
 */
char *char_duplicate(char *place, int x, int y)
{
	static char buffer[1024];
	int i = 0, k = 0;
	for (k = 0, i = x; i < y; i++)
		if (place[i] != ':')
			buffer[k++] = place[i];
	buffer[k] = 0;
	return (buffer);
}
/**
 * path_finder - find the path
 * 
 * @info: struct
 * 
 * @place: string
 * 
 * @commandd: commandd to find the path
 *
 * Return: full path
 */
char *path_finder(info_t *info, char *place, char *commandd)
{
	int i = 0, p = 0;
	char *path;
	if (!place)
		return (NULL);
	if ((_strlength(commandd) > 2) && starts_with(commandd, "./"))
	{
		if (is_command(info, commandd))
			return (commandd);
	}
	while (1)
	{
		if (!place[i] || place[i] == ':')
		{
			path = char_duplicate(place, p, i);
			if (!*path)
				_strcat(path, commandd);
			else
			{
				_strcat(path, "/");
				_strcat(path, commandd);
			}
			if (is_command(info, path))
				return (path);
			if (!place[i])
				break;
			p = i;
		}
		i++;
	}
	return (NULL);
}
