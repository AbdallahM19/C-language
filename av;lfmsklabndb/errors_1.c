#include "shell.h"

/**
 * _erratoi - convert a string to an integer
 * @string: the only member
 * Return: result or -1
*/
int _erratoi(char *string)
{
	int i = 0;
	unsigned long int res = 0;

	if (*string == '+')
		string++;
	for (i = 0;  string[i] != '\0'; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			res *= 10;
			res += (string[i] - '0');
			if (res > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (res);
}

/**
 * print_error - print error massage to stderr
 * @info: pointer to the struct
 * @str: string to be printed
 * Return: void
*/
void print_error(info_t *info, char *str)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(str);
}

/**
 * print_integer - print an integer to a filedescriptor
 * @input: number
 * @fd: tfile
 * Return: character
*/
int print_d(int input, int fd)
{
	int (*p_putchar)(char) = _putchar;
	int i, c = 0;
	unsigned int res, cur;

	if (fd == STDERR_FILENO)
		p_putchar = _eputchar;
	if (input < 0)
	{
		res = -input;
		p_putchar('-');
		c++;
	}
	else
		res = input;
	cur = res;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (res / i)
		{
			p_putchar('0' + cur / i);
			c++;
		}
		cur %= i;
	}
	p_putchar('0' + cur);
	c++;
	return (c);
}

/**
 * convert_number - convert a number
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: a string
*/
char *convert_number(long int num, int base, int flags)
{
	static char *array;
	static char buf[50];
	char sign = 0, *str;
	unsigned long i = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		i = -num;
		sign = '-';

	}
	array = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	str = &buf[49];
	*str = '\0';
	do	{
		*--str = array[i % base];
		i /= base;
	} while (i != 0);
	if (sign)
		*--str = sign;
	return (str);
}

/**
 * remove_comments - remove comments
 * @cat: pointer
 * Return: Always 0;
 */
void remove_comments(char *cat)
{
	int x = 0;

	while (buf[x] != '\0')
	{
		if (buf[x] == '#' && (!x || buf[x - 1] == ' '))
		{
			buf[x] = '\0';
			break;
		}
		x++;
	}
}