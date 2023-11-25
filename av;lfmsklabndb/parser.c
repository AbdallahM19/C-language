#include "shell.h"

/**
 * is_cmd - check if it is command
 * @info: pointer to struct
 * @path: the path
 * Return: 1 if true, 0 otherwise
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);
	if (st.st_mode & S_IFREG)
		return (1);
	return (0);
}

/**
 * dup_chars - dublicate a char
 * @pathstr: path
 * @start: start
 * @stop: stop
 * Return: pointer to new buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buf[1024];
	int i = 0, k = 0;

	i = start;
	while (i < stop)
	{
		if (pathstr[i] != ':')
			buf[k++] = pathstr[i];
		i++;
	}
	buf[k] = 0;
	return (buf);
}

/**
 * find_path - find the path
 * @info: struct
 * @pathstr: string
 * @cmd: commandd to find the path
 * Return: full path
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int i = 0, cur = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[i] || pathstr[i] == ':')
		{
			p = dup_chars(pathstr, cur, i);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[i])
				break;
			cur = i;
		}
		i++;
	}
	return (NULL);
}