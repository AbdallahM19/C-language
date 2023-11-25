#include "shell.h"
/**
 * start_history - get file of history
 * 
 * @info: pointer to the struct
 *
 * Return: pointer
 */
char *start_history(info_t *info)
{
	char *buffer, *x;
	x = _getenv(info, "HOME=");
	if (!x)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlength(x) + _strlength(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, x);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}
/**
 * history_writing- creat or append a file
 * 
 * @info: pointer to the struct
 *
 * Return: 1 or-1
 */
int history_writing(info_t *info)
{
	ssize_t file;
	char *filename = start_history(info);
	list_t *cat = NULL;
	if (!filename)
		return (-1);

	file = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (file == -1)
		return (-1);
	for (cat = info->history; cat; cat = cat->next)
	{
		_putsfd(cat->str, file);
		_putfd('\n', file);
	}
	_putfd(BUF_FLUSH, file);
	close(file);
	return (1);
}
/**
 * history_reading - reads history 
 * 
 * @info: pointer to a struct
 *
 * Return: histcount 
 */
int history_reading(info_t *info)
{
	int i, last = 0, linecount = 0;
	ssize_t file, reading, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = start_history(info);

	if (!filename)
		return (0);

	file = open(filename, O_RDONLY);
	free(filename);
	if (file == -1)
		return (0);
	if (!fstat(file, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	reading = read(file, buf, fsize);
	buf[fsize] = 0;
	if (reading <= 0)
		return (free(buf), 0);
	close(file);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_history_list(info, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_history_list(info, buf + last, linecount++);
	free(buf);
	info->histcount = linecount;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	history_renum(info);
	return (info->histcount);
}

/**
 * create_history_list - make a list to handle the history
 * 
 * @info: first parameter
 * 
 * @buffer: seconed one
 * 
 * @count: third one
 *
 * Return: (0)
 */
int create_history_list(info_t *info, char *buffer, int count)
{
	list_t *cat = NULL;

	if (info->history)
		cat = info->history;
	add_node_end(&cat, buffer, count);

	if (!info->history)
		info->history = cat;
	return (0);
}
/**
 * history_renum - update the history
 * 
 * @info: pointer to Struct
 *
 * Return: the new histcount
 */
int history_renum(info_t *info)
{
	list_t *cat = info->history;
	int x = 0;
	while (cat)
	{
		cat->num = x++;
		cat = cat->next;
	}
	return (info->histcount = x);
}
