#include "shell.h"

/**
 * get_history_file - get file of history
 * @info: pointer to the struct
 * Return: pointer
 */
char *get_history_file(info_t *info)
{
	char *buffer, *str;

	str = _getenv(info, "HOME=");
	if (!str)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(str) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, str);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creat or append a file
 * @info: pointer to the struct
 * Return: 1 or-1
 */
int write_history(info_t *info)
{
	ssize_t fd;
	char *name_file = get_history_file(info);
	list_t *node = NULL;

	if (!name_file)
		return (-1);
	fd = open(name_file, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name_file);
	if (fd == -1)
		return (-1);
	node = info->history;
	while (node)
	{
		_putsfd(node->str, fd);
		_putfd('\n', fd);
		node = node->next;
	}
	_putfd(BUF_FLUSH, fd);
	close(fd);
	return (1);
}

/**
 * read_history - reads history
 * @info: pointer to a struct
 * Return: histcount
 */
int read_history(info_t *info)
{
	int i = 0, last = 0, linecount = 0;
	ssize_t fd, rdlen, fsize = 0;
	struct stat st;
	char *buffer = NULL, *name_file = get_history_file(info);

	if (!name_file)
		return (0);
	fd = open(name_file, O_RDONLY);
	free(name_file);
	if (fd == -1)
		return (0);
	if (!fstat(fd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buffer = malloc(sizeof(char) * (fsize + 1));
	if (!buffer)
		return (0);
	rdlen = read(fd, buffer, fsize);
	buffer[fsize] = 0;
	if (rdlen <= 0)
		return (free(buffer), 0);
	close(fd);
	while (i < fsize)
	{
		if (buffer[i] == '\n')
		{
			buffer[i] = 0;
			build_history_list(info, buffer + last, linecount++);
			last = i + 1;
		}
		i++;
	}
	if (last != i)
		build_history_list(info, buffer + last, linecount++);
	free(buffer);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info), return (info->histcount);
}

/**
 * build_history_list - make a list to handle the history
 * @info: first parameter
 * @buf: seconed one
 * @linecount: third one
 * Return: (0)
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);
	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - update the history
 * @info: pointer to Struct
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int i;

	for (i = 0; node; node = node->next;)
		node->num = i++;
	return (info->histcount = i);
}