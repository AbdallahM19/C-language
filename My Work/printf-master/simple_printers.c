#include "main.h"

/**
 * print_rot13 - print str by rot13
 * @ap: str
 * @par: the param struct
 * Return: num of printed
*/

int print_rot13(va_list ap, par_t *par)
{
	int i, in;
	int c = 0;
	char arr[] = "NOPQRSTUVWXYZABCDEFGHIJKLM    nopqrstuvwxyzabcdefghijklm";
	char *p = va_arg(ap, char *);
	(void)par;

	i = 0;
	in = 0;
	while (p[i])
	{
		if ((p[i] >= 'A' && p[i] <= 'Z') ||
		(p[i] >= 'a' && p[i] <= 'z'))
		{
			in = p[i] - 65;
			c += _putchar(arr[in]);
		}
		else
			c += _putchar(p[i]);
		i++;
	}
	return (c);
}

/**
 * print_rev - rev string
 * @ap: str
 * @par: the param struct
 * Return: sum
*/

int print_rev(va_list ap, par_t *par)
{
	int l, s = 0;
	char *str = va_arg(ap, char *);
	UNUSED(par);

	if (str)
	{
		for (l = 0; *str; str++)
			l++;
		str--;
		for (; l > 0; l--, str--)
			s += _putchar(*str);
	}
	return (s);
}

/**
 * print_from_to - print range of char
 * @start: start add
 * @stop: stop add
 * @except: except add
 * Return: num printed
*/

int print_from_to(char *start, char *stop, char *except)
{
	int i = 0;

	while (start <= stop)
	{
		if (start != except)
			i += _putchar(*start);
		start++;
	}
	return (i);
}