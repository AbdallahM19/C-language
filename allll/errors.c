#include "shell.h"

/**
 * _eputs - print a string to stderr
 * @str: ta string
 * Return: void
*/
void _eputs(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
		_eputchar(str[i]);
}

/**
 * _eputchar - print a char to stderr
 * @c: a char
 * Return: the char
 */
int _eputchar(char c)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 * _putfd - print a char to a filedescriptor
 * @c: a character
 * @fd: a filedescriptor
 * Return: the char
*/
int _putfd(char c, int fd)
{
	static int i;
	static char buffer[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buffer, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buffer[i++] = c;
	return (1);
}

/**
 *_putsfd - print a string to a filedescriptor
 * @str: a string
 * @fd: the filedescriptor to write to
 * Return: the number of chars put
*/
int _putsfd(char *str, int fd)
{
	int x = 0;

	if (!str)
		return (0);
	while (*str)
		x += _putfd(*str++, fd);
	return (x);
}