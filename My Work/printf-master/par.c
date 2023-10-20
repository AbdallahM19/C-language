#include "main.h"

/**
 *init_par - function clears struct fields and reset buf
 *@par: the parameter of struct
 *@ap: the argument pointer
 *Return: void
 */

void init_par(par_t *par, va_list ap)
{
	UNUSED(ap);
	par->unsign = 0;
	par->plus_flag = 0;
	par->space_flag = 0;
	par->hashtag_flag = 0;
	par->zero_flag = 0;
	par->minus_flag = 0;

	par->width = 0;
	par->percision = UINT_MAX;

	par->h_modifier = 0;
	par->l_modifier = 0;
}
