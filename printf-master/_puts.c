#include "main.h"

/**
 * _putchar - write the char c
 * @c: char
 * Return: succes 1 or error -1
 */
int _putchar(int c)
{
	static int a;
	static char buff[BUFFER_SIZE];

	if (c == BUFF_F || a >= BUFFER_SIZE)
	{
		write(1, buff, a);
		a = 0;
	}
	if (c != BUFF_F)
		buff[a++] = c;
	return (1);
}

/**
 *_puts - function prints a string with newline
 *@str: string to print
 *Return: void
 */
int _puts(char *str)
{
	char *s = str;

	while (*str)
		_putchar(*str++);
	return (str - s);
}
