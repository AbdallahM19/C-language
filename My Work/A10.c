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

	int padding = par->width - 1;

	if (par->minus_flag)
	{
		_putchar('%');
		_putchar('r');
		while (padding > 0)
		{
			_putchar(' ');
			padding--;
		}
	}
	else
	{
		char pad_char = (par->zero_flag) ? '0' : ' ';
		while (padding > 0)
		{
			_putchar(pad_char);
			padding--;
		}
		_putchar('%');
		_putchar('r');
	}
	return (par->width);
}