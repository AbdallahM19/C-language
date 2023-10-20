#include "main.h"

/**
 **convert - a converter function, itoa copy
 *@num: a number
 *@base: a base
 *@flag: an argument flag
 *@par: a parameter struct
 *Return: a string
 */

char *convert(long int num, int base, int flag, par_t *par)
{
	static char *arr;
	static char fer[50];
	char sign = 0;
	char *p;
	unsigned long n = num;
	UNUSED(par);

	if (!(flag && CON_UNSIGN) && num < 0)
	{
		n = -num;
		sign = '-';
	}
	arr = flag & CON_UNSIGN ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &fer[49];
	*p = '\0';

	do {
		*--p = arr[n % base];
		n /= base;
	} while (n != 0);

	if (sign)
		*--p = sign;
	return (p);
}


/**
 *print_unsign - function prints an unsigned int number
 *@ap: an argument pointer
 *@par: pararmeter struct
 *Return: the bytes
 */
int print_unsign(va_list ap, par_t *par)
{
	unsigned long l;

	if (par->l_modifier)
		l = (unsigned long)va_arg(ap, unsigned long);
	else if (par->h_modifier)
		l = (unsigned short int)va_arg(ap, unsigned int);
	else
		l = (unsigned int)va_arg(ap, unsigned int);

	par->unsign = 1;
	return (print_num(convert(l, 10, CON_UNSIGN, par), par));
}

/**
 *print_addr - function prints address
 *@ap: an argument pointer
 *@par: pararmeter struct
 *Return: the bytes
*/

int print_addr(va_list ap, par_t *par)
{
	unsigned long int n = va_arg(ap, unsigned long int);
	char *str;

	if (!n)
		return (_puts("(nil)"));

	str = convert(n, 16, CON_UNSIGN | CON_LOWER, par);
	*--str = 'x';
	*--str = '0';

	return (print_num(str, par));
}
