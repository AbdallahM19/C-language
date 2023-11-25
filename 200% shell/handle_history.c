#include "shell.h"

/**
 * start_history - get file of history
 * @argument: pointer to the struct
 * Return: pointer
 */
char *start_history(struct_t *argument)
{
	char *buffer, *x;
	x = get_env(argument, "HOME=");
	if (!x)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlength(x) + _strlength(HIST_FILE) + 2));
	if (!buffer)
	{
		free(x);
		return (NULL);
	}
	buffer[0] = 0;
	_strcpy(buffer, x);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	free(x);
	return (buffer);
}

/**
 * history_writing- creat or append a file
 * @argument: pointer to the struct
 * Return: 1 or-1
 */
int history_writing(struct_t *argument)
{
	ssize_t file;
	char *filename = start_history(argument);
	list_t *cat = NULL;

	if (!filename)
		return (-1);

	file = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);

	if (file == -1)
		return (-1);
	for (cat = argument->history; cat; cat = cat->next)
	{
		_putsfd(cat->string, file);
		_putfd('\n', file);
	}
	_putfd(NEGATIVE, file);
	close(file);
	return (1);
}

/**
 * history_reading - reads history
 * @argument: pointer to a struct
 * Return: histcount
 */
int history_reading(struct_t *argument)
{
int i, last = 0, linecount = 0;
ssize_t file, reading, fsize = 0;
struct stat st;
char *buf = NULL, *filename = start_history(argument);
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
	{
		close(file);
		return (0);
	}
	reading = read(file, buf, fsize);
	buf[fsize] = 0;
	if (reading <= 0)
		return (free(buf), 0);
	close(file);
	for (i = 0; i < fsize; i++)
		if (buf[i] == '\n')
		{
			buf[i] = 0;
			create_history_list(argument, buf + last, linecount++);
			last = i + 1;
		}
	if (last != i)
		create_history_list(argument, buf + last, linecount++);
	free(buf);
	argument->histcount = linecount;
	while (argument->histcount-- >= HIST_MAX)
		delete_node_at_index(&(argument->history), 0);
	history_renum(argument);
	return (argument->histcount);
}

/**
 * create_history_list - make a list to handle the history
 * @argument: first parameter
 * @buffer: seconed one
 * @count: third one
 * Return: (0)
 */
int create_history_list(struct_t *argument, char *buffer, int count)
{
	list_t *cat = NULL;

	if (argument->history)
		cat = argument->history;
	add_node_end(&cat, buffer, count);

	if (!argument->history)
		argument->history = cat;
	return (0);
}

/**
 * history_renum - update the history
 * @argument: pointer to Struct
 * Return: the new histcount
 */
int history_renum(struct_t *argument)
{
list_t *cat = argument->history;
int i = 0;
	while (cat)
	{
		cat->n = i++;
		cat = cat->next;
	}
	return (argument->histcount = i);
}
