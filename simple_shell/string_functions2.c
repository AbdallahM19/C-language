#include "shell.h"

/**
 * _strcpy - copies a string from one pointer to another
 *	including the terminating null byte (\0)
 * @src: source of string parameter input
 * @dest: destination of string
 * Return: pointer to dest input parameter
*/

char *_strcpy(char *dest, char *src)
{
	int i = 0;

	if (dest == src || src == 0)
		return (dest);
	while (src[i])
	{
		dest[i] = src[i];
		i++;
	}
	dest[i] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @src: source of string parameter duplicate
 * Return: pointer to dest duplicate parameter
*/
char *_strdup(const char *str)
{
	int lenght = 0;
	char *ret;

	if (str == NULL)
		return (NULL);
	while (*str++)
		lenght++;
	ret = malloc(sizeof(char) * (lenght + 1));
	if (!ret)
		return (NULL);
	for (lenght ++; lenght--;)
		ret[lenght] = *--str;
	return (ret);
}

/**
 * _puts - Write a function that prints a string,
 *              followed by a new line, to stdout.
 * @str: string parameter to print
 */

void _puts(char *str)
{
	int i = 0;

	if (!str)
		return;
	while (str[i] != '\0')
	{
		_putchar(str[i]);
		i++;
	}
}

/**
 * _putchar - writes the character c to stdout
 * @c: The character to print
 * Return: On success 1.
 *         On error, -1 is returned, and errno is set appropriately.
 */

int _putchar(char c)
{
	static int i;
	static char buf[write_BUF_SIZE];

	if (c == BUF_FLUSH || i >= write_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}