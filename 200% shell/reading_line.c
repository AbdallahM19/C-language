#include "shell.h"
/**
 * buffer_reading- buffer reading
 *
 * @argument: pointer to struct
 *
 * @buffer: buffer
 *
 * @size: size
 *
 * Return: x
 */
ssize_t buffer_reading(struct_t *argument, char *buffer, size_t *size)
{
ssize_t x = 0;
	if (*size)
		return (0);
	x = read(argument->readfd, buffer, BUFFER_RD);
	if (x >= 0)
		*size = x;
	return (x);
}
/**
 * _getline - read from line
 *
 * @argument: pointer to struct
 *
 * @buffer: pointer of pointer
 *
 * @length: length of line
 *
 * Return: s
 */
int _getline(struct_t *argument, char **buffer, size_t *length)
{
static size_t i, len;
static char buf[BUFFER_RD];
ssize_t r = 0, s = 0;
size_t k;
char *p = NULL, *new_p = NULL, *c;
	p = *buffer;
	if (p && length)
		s = *length;
	if (i == len)
		i = len = 0;
	r = buffer_reading(argument, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	k = c ? 1 + (unsigned int)(c - buf) : len;
	new_p = _realloc(p, s, s ? s + k : k + 1);
	if (!new_p)
		return (p ? free(p), -1 : -1);

	if (s)
		_strncat(new_p, buf + i, k - i);
	else
		_strncpy(new_p, buf + i, k - i + 1);
s += k - i;
i = k;
p = new_p;
	if (length)
		*length = s;
	*buffer = p;
	return (s);
}
/**
* handle_input- handle buffer
*
* @argument: first parameter
*
* @buffer: seconed one
*
* @length: third one
*
* Return: the input
*/
ssize_t handle_input(struct_t *argument, char **buffer, size_t *length)
{
	ssize_t r = 0;
	size_t len_p = 0;

	if (!*length)
	{
		free(*buffer);
		*buffer = NULL;
		signal(SIGINT, handle_sign);
#if USE_GETLINE
		r = getline(buf, &len_p, stdin);
#else
		r = _getline(argument, buffer, &len_p);
#endif
		if (r > 0)
		{
			if ((*buffer)[r - 1] == '\n')
			{
				(*buffer)[r - 1] = '\0';
				r--;
			}
			argument->linecount_flag = 1;
			remove_comments(*buffer);
			create_history_list(argument, *buffer, argument->histcount++);
			/* if (_strchr(*buf, ';')) is this a command chain? */
			{
				*length = r;
				argument->cmd_buf = buffer;
			}
		}
	}
	return (r);
}
/**
 * get_input - read from a line
 *
 * @argument: pointer to struct
 *
 * Return: bytes read
 */
ssize_t get_input(struct_t *argument)
{
static char *buffer;
static size_t i, j, length;
ssize_t r = 0;
char **buf_g = &(argument->arg), *p;
	_putchar(NEGATTIVE);
	r = handle_input(argument, &buffer, &length);
	if (r == -1)
		return (-1);
	if (length)
	{
		j = i;
		p = buffer + i;
		check_chain(argument, buffer, &j, i, length);
		while (j < length)
		{
			if (is_chain(argument, buffer, &j))
				break;
			j++;
		}

		i = j + 1;
		if (i >= length)
		{
			i = length = 0;
			argument->cmd_buf_type = CMD_NORM;
		}
		*buf_g = p;
		return (_strlength(p));
	}

	*buf_g = buffer;
	return (r);
}
