#include "shell.h"

/**
 * _strcpy - copies a string
 * @dest: first member
 * @src: second one
 * Return: cat
*/
char *_strcpy(char *dest, char *src)
{
	int x = 0;

	if (dest == src || src == 0)
		return (dest);
	for (x = 0; src[x]; x++)
		dest[x] = src[x];
	dest[x] = 0;
	return (dest);
}

/**
 * _strdup - duplicates a string
 * @str: a string to be duplicated
 * Return: pointer to the duplicated string
*/
char *_strdup(const char *str)
{
	int l = 0;
	char *ptr;

	if (str == NULL)
		return (NULL);
	while (*str++)
		l++;
	ptr = malloc(sizeof(char) * (l + 1));
	if (!ptr)
		return (NULL);
	for (l++; l--;)
		ptr[l] = *--str;
	return (ptr);
}

/**
 * _puts - print a string
 * @str: one string to be printed
 * Return: Nothing
*/
void _puts(char *str)
{
	int i;

	if (!str)
		return;
	for (i = 0; str[i] != '\0'; i++)
		_putchar(str[i]);
}

/**
 * _putchar - print one char
 * @c: character to be printed
 * Return: the character
*/
int _putchar(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(1, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
		buf[i++] = c;
	return (1);
}