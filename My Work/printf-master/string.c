#include "main.h"

/**
 * get_perci - gets the precision from the format str to the param struct
 * @p: format str
 * @ap: argument pointer
 * @par: struct
 * Return: pointer
*/

char *get_perci(char *p, par_t *par, va_list ap)
{
	int a = 0;

	if (*p != '.')
		return (p);
	p++;
	if (*p == '*')
	{
		a = va_arg(ap, int);
		p++;
	}
	else
	{
		while (_isdig(*p))
			a = a * 10 + (*p++ - '0');
	}
	par->percision = a;
	return (p);
}
