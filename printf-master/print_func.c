#include "main.h"

/**
 * print_char - Prints a char
 * @ap: List a of arguments pointer
 * @par: struct
 * Return: Num of chars printed
 */
int print_char(va_list ap, par_t *par)
{
	char p_c = va_arg(ap, int);
	unsigned int p = 1, sum = 0, c = va_arg(ap, int);

	if (par->minus_flag)
		sum += _putchar(c);
	while (p++ < par->width)
		sum += _putchar(p_c);
	if (!par->minus_flag)
		sum += _putchar(c);

	return (sum);
}

/**
 * print_string - Prints a string
 * @ap: List a of arguments pointer
 * @par: struct
 * Return: Num of chars printed
 */
int print_string(va_list ap, par_t *par)
{
	char *str = va_arg(ap, char *), p_c = ' ';
	unsigned int p = 0, sum = 0, i = 0, l;

	UNUSED(par);
	switch ((int)(!str))
		case 1:
			str = NULL_STR;

	l = p = _strlen(str);
	if (par->percision < p)
		l = p = par->percision;
	if (par->minus_flag)
	{
		if (par->percision != UINT_MAX)
			for (i = 0; i < p; i++)
				sum += _putchar(*str++);
		else
			sum += _puts(str);
	}
	while (l++ < par->width)
		sum += _putchar(p_c);
	if (!par->minus_flag)
	{
		if (par->percision != UINT_MAX)
			for (i = 0; i < p; i++)
				sum += _putchar(*str++);
		else
			sum += _puts(str);
	}

	return (sum);
}

/**
 * print_percent - Prints a percent
 * @ap: List a of arguments pointer
 * @par: struct
 * Return: Num of chars printed
 */
int print_percent(va_list ap, par_t *par)
{
	UNUSED(ap);
	UNUSED(par);
	return (_putchar('%'));
}

/**
 * print_int - Prints a integer
 * @ap: List a of arguments pointer
 * @par: struct
 * Return: Num of chars printed
 */
int print_int(va_list ap, par_t *par)
{
	long i;

	if (par->l_modifier)
		i = va_arg(ap, long);
	else if (par->h_modifier)
		i = (short int)va_arg(ap, int);
	else
		i = (int)va_arg(ap, int);

	return (print_num(convert(i, 10, 0, par), par));
}

/**
 * print_S - format specifier
 * @ap: List a of arguments pointer
 * @par: struct
 * Return: Num of chars printed
 */
int print_S(va_list ap, par_t *par)
{
	char *str = va_arg(ap, char *);
	char *hex;
	int sum = 0;

	if ((int)(!str))
		return (_puts(NULL_STR));
	for (; *str; str++)
	{
		if ((*str > 0 && *str < 32) || *str >= 127)
		{
			sum += _putchar('\\');
			sum += _putchar('x');
			hex = convert(*str, 16, 0, par);
			if (!hex[1])
				sum += _putchar('0');
			sum += _puts(hex);
		}
		else
		{
			sum += _putchar(*str);
		}
	}
	return (sum);
}