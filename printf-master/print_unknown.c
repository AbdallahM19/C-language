#include "main.h"

/**
 * print_unknown - Handle unknown specifiers
 * @ap: List of arguments pointer
 * @par: struct
 * Return: Number of characters printed
 */
int print_unknown(va_list ap, par_t *par)
{
	UNUSED(ap);
	if (par->minus_flag)
	{
		_putchar('%');
		_putchar('r');
		while (par->width-- > 2)
			_putchar(' ');
	}
	else
	{
		while (par->width-- > 2)
		{
			if (par->zero_flag)
				_putchar('0');
			else
				_putchar(' ');
		}
		_putchar('%');
		_putchar('r');
	}
	return (par->width + 2);
}