#include "main.h"

/**
 **get_speci - function finds format function
 *@s: a format string
 *Return: byts numbers to print
 */

int (*get_speci(char *s))(va_list ap, par_t *par)
{
	spec_t specifiers[] = {
		{"c", print_char},
		{"d", print_int},
		{"i", print_int},
		{"s", print_string},
		{"%", print_percent},
		{"o", print_oct},
		{"b", print_binary},
		{"x", print_hex},
		{"X", print_HEX},
		{"u", print_unsign},
		{"p", print_addr},
		{"S", print_S},
		{"R", print_rot13},
		{"r", print_unknown},
		{NULL, NULL}
	};
	int i = 0;

	while (specifiers[i].spec)
	{
		if (*s == specifiers[i].spec[0])
			return (specifiers[i].f);
		i++;
	}
	return (print_unknown);
}

/**
 *get_print_fun - function finds format func
 *@s: the string format
 *@ap: an argument pointer
 *@par: a parameter struct
 *Return: bytes number to print
 */

int get_print_fun(char *s, va_list ap, par_t *par)
{
	int (*f)(va_list, par_t *) = get_speci(s);

	if (f)
		return (f(ap, par));
	return (0);
}
/**
 *get_flag - function finds flag func
 *@s: the format string
 *@par: a parameter struct
 *Return: if vaild flag
 */

int get_flag(char *s, par_t *par)
{
	int f = 0;

	switch (*s)
	{
		case '+':
			f = par->plus_flag = 1;
			break;
		case ' ':
			f = par->space_flag = 1;
			break;
		case '#':
			f = par->hashtag_flag = 1;
			break;
		case '-':
			f = par->minus_flag = 1;
			break;
		case '0':
			f = par->zero_flag = 1;
			break;
	}
	return (f);
}

/**
 **get_width - function gets width from format string
 *@s: the format string
 *@par: a parameter struct
 *@ap: an argument pointer
 *Return: a new pointer
 */

char *get_width(char *s, par_t *par, va_list ap)
{
	int w = 0;

	if (*s == '*')
	{
		w = va_arg(ap, int);
		s++;
	}
	else
	{
		while (_isdig(*s))
			w = w * 10 + (*s++ - '0');
	}

	par->width = w;
	return (s);
}

/**
 *get_modif - function finds the modifier func
 *@s: the format string
 *@par: the parameter struct
 *Return: if valid modifier
 */

int get_modif(char *s, par_t *par)
{
	int m = 0;

	switch (*s)
	{
		case 'h':
			m = par->h_modifier = 1;
			break;
		case 'l':
			m = par->l_modifier = 1;
			break;
	}
	return (m);
}
