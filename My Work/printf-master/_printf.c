#include "main.h"

/**
 *_printf - function prints all things
 *@format: a format string
 *Return: printed bytes number
 */

int _printf(const char *format, ...)
{
	int sum = 0;
	va_list ap;
	char *p, *start;
	par_t par = PARAMS_INIT;

	va_start(ap, format);

	if (!format || (format[0] == '%' && !format[1]))
		return (-1);
	if (format[0] == '%' && format[1] == ' ' && !format[2])
		return (-1);
	for (p = (char *)format; *p; p++)
	{
		init_par(&par, ap);
		if (*p != '%')
		{
			sum += _putchar(*p);
			continue;
		}
		start = p;
		p++;

		if (*p == 'c')
		{
			char c = va_arg(ap, int);
			sum += _putchar(c);
			continue;
		}
		while (get_flag(p, &par))
		{
			p++;
		}
		p = get_width(p, &par, ap);
		p = get_perci(p, &par, ap);
		if (get_modif(p, &par))
			p++;
		if (!get_speci(p))
			sum += print_from_to(start, p, par.l_modifier || par.h_modifier ? p - 1 : 0);
		else
			sum += get_print_fun(p, ap, &par);
	}
	_putchar(BUFF_F);
	va_end(ap);
	return (sum);
}