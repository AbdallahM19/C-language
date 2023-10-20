#include "main.h"

/**
 * print_binary - Prints an unsigned integer in binary format
 * @ap: List of arguments pointer
 * @par: struct
 * Return: Num of characters printed
 */
int print_binary(va_list ap, par_t *par)
{
	unsigned int num = va_arg(ap, unsigned int);
	char *s = convert(num, 2, CON_UNSIGN, par);
	int i = 0;

	if (par->hashtag_flag && num)
		*--s = '0';
	par->unsign = 1;
	return (i += print_num(s, par));
}

/**
 * print_oct - Prints an unsigned integer in octal format
 * @ap: List of arguments pointer
 * @par: struct
 * Return: Num of characters printed
 */
int print_oct(va_list ap, par_t *par)
{
	unsigned long l;
	char *str;
	int i = 0;

	if (par->l_modifier)
		l = (unsigned long)va_arg(ap, unsigned long);
	else if (par->h_modifier)
		l = (unsigned short int)va_arg(ap, unsigned int);
	else
		l = (unsigned int)va_arg(ap, unsigned int);

	str = convert(l, 8, CON_UNSIGN, par);
	if (par->hashtag_flag && l)
		*--str = '0';
	par->unsign = 1;
	return (i += print_num(str, par));
}

/**
 * print_HEX - Prints an unsigned integer in hex format uppercase
 * @ap: List of arguments pointer
 * @par: struct
 * Return: Num of characters printed
 */
int print_HEX(va_list ap, par_t *par)
{
	unsigned long l;
	int c = 0;
	char *str;
	int i = 0;

	if (par->l_modifier)
		l = (unsigned long)va_arg(ap, unsigned long);
	else if (par->h_modifier)
		l = (unsigned short int)va_arg(ap, unsigned int);
	else
		l = (unsigned int)va_arg(ap, unsigned int);

	str = convert(l, 16, CON_UNSIGN, par);
	if (par->hashtag_flag && l)
	{
		*--str = 'X';
		*--str = '0';
	}
	par->unsign = 1;

	while (str[i] != '\0')
	{
		if (str[i] >= 'a' && str[i] <= 'f')
			str[i] = str[i] - 32;
		i++;
	}
	return (c += print_num(str, par));
}

/**
 * print_hex - Prints an unsigned integer in hex format
 * @ap: List of arguments pointer
 * @par: struct
 * Return: Num of characters printed
 */
int print_hex(va_list ap, par_t *par)
{
	unsigned long l;
	int c = 0;
	char *str;

	if (par->l_modifier)
		l = (unsigned long)va_arg(ap, unsigned long);
	else if (par->h_modifier)
		l = (unsigned short int)va_arg(ap, unsigned int);
	else
		l = (unsigned int)va_arg(ap, unsigned int);

	str = convert(l, 16, CON_UNSIGN, par);

	if (par->hashtag_flag && l)
	{
		*--str = 'x';
		*--str = '0';
	}
	par->unsign = 1;
	return (c += print_num(str, par));
}
