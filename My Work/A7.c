#include "main.h"

/**
 * print_rot13 - print str by rot13
 * @ap: str
 * @par: the param struct
 * Return: num of printed
*/

int print_rot13(va_list ap, par_t *par)
{
	int i = 0, in = 0;
	int sum = 0;
	char arr[] = "ABCDEFGHIJKLMNOPQRSTUVWXYZ    abcdefghijklmnopqrstuvwxyz";
	(void)par;
	char *p = va_arg(ap, char *);

	while (p[i])
	{
		if ((p[i] >= 'A' && p[i] <= 'Z') ||
		(p[i] >= 'a' && p[i] <= 'z'))
		{
			in = p[i] - 65;
			sum += _putchar(arr[in]);
		}
		else
			sum += _putchar(p[i]);
		i++;
	}
	return (sum);
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

	UNUSED(par);
	char *str = va_arg(ap, char *);

	if (str)
	{
		for (l = 0; *str; str++)
			l++;
		str--;
		for (; l > 0; l--)
		{
			s += _putchar(*str);
			str--;
		}
	}
	return (s);
}

/**
 * print_f_t - print range of char
 * @start: start add
 * @stop: stop add
 * @except: except add
 * Return: num printed
*/

int print_f_t(char *start, char *stop, char *except)
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