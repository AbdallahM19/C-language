#include "main.h"

/**
 * _strlen - len of string
 * @s: string
 * Return: int len str
 */
int _strlen(char *s)
{
	int i = 0;

	while (*s++)
		i++;
	return (i);
}

/**
 * _isdig - check if char is digit
 * @c: char
 * Return: digit
 */
int _isdig(int c)
{
	return (c >= '0' && c <= '9');
}

/**
 * print_num - print a num
 * @str: base num like string
 * @par: struct
 * Return: char printed
 */
int print_num(char *str, par_t *par)
{
	unsigned int i = _strlen(str);
	int n = (!par->unsign && *str == '-');

	if (!par->percision && *str == '0' && !str[1])
		str = "";
	if (n)
	{
		str++;
		i--;
	}
	if (par->percision != UINT_MAX)
		while (i++ < par->percision)
			*--str = '0';
	if (n)
		*--str = '-';
	if (!par->minus_flag)
		return (print_num_r_shift(str, par));
	else
		return (print_num_l_shift(str, par));
}

/**
 * print_num_r_shift - print a num
 * @str: base num like string
 * @par: struct
 * Return: char printed
 */
int print_num_r_shift(char *str, par_t *par)
{
	unsigned int l = 0, n, n2, i = _strlen(str);
	char p_ch = ' ';

	if (par->zero_flag && !par->minus_flag)
		p_ch = '0';
	n = n2 = (!par->unsign && *str == '-');
	if (n && i < par->width && p_ch == '0' && !par->minus_flag)
		str++;
	else
		n = 0;
	if ((par->plus_flag && !n2) ||
			(!par->plus_flag && par->space_flag && !n2))
		i++;
	if (n && p_ch == '0')
		l += _putchar('-');
	if (par->plus_flag && !n2 && p_ch == '0' && !par->unsign)
		l += _putchar('+');
	else if (!par->plus_flag && par->space_flag && !n2 &&
			!par->unsign && par->zero_flag)
		l += _putchar(' ');
	while (i++ < par->width)
		l += _putchar(p_ch);
	if (n && p_ch == ' ')
		l += _putchar('-');
	if (par->plus_flag && !n2 && p_ch == ' ' && !par->unsign)
		l += _putchar('+');
	else if (!par->plus_flag && par->space_flag && !n2 &&
			!par->unsign && !par->zero_flag)
		l += _putchar(' ');
	l += _puts(str);
	return (l);
}

/**
 * print_num_l_shift - print a num
 * @str: base num like string
 * @par: struct
 * Return: char printed
 */
int print_num_l_shift(char *str, par_t *par)
{
	unsigned int l = 0, n, n2, i = _strlen(str);
	char p_ch = ' ';

	if (par->zero_flag && !par->minus_flag)
		p_ch = '0';
	n = n2 = (!par->unsign && *str == '-');
	if (n && i < par->width && p_ch == '0' && !par->minus_flag)
		str++;
	else
		n = 0;

	if (par->plus_flag && !n2 && !par->unsign)
	{
		l += _putchar('+');
		i++;
	}
	else if (par->space_flag && !n2 && !par->unsign)
	{
		l += _putchar(' ');
		i++;
	}
	l += _puts(str);
	while (i++ < par->width)
		l += _putchar(p_ch);
	return (l);
}
