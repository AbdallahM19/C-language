#include "shell.h"
/**
 * print_integer - print an integer to a filedescriptor
 * @num: number
 * @file: tfile
 * Return: character
*/
int print_integer(int num, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int string, current;

	if (file == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		string = -num;
		__putchar('-');
		count++;
	}
	else
		string = num;
	current = string;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (string / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}

/**
 * _putfd - print a char to a filedescriptor
 * @ch: a character
 * @file: a filedescriptor
 * Return: the char
*/
int _putfd(char ch, int file)
{
	static int x;
	static char buf[BUFFER_WR];

	if (ch == NEGATTIVE || x >= BUFFER_WR)
	{
		write(file, buf, x);
		x = 0;
	}
	if (ch != NEGATTIVE)
		buf[x++] = ch;
	return (1);
}
/**
 *_putsfd - print a string to a filedescriptor
 * @cat: a string
 * @file: the filedescriptor to write to
 * Return: the number of chars put
*/
int _putsfd(char *cat, int file)
{
	int x = 0;

	if (!cat)
		return (0);
	while (*cat)
	{
		x += _putfd(*cat++, file);
	}
	return (x);
}
