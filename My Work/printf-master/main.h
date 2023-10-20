#ifndef MAIN_H
#define MAIN_H

#include <stdio.h>
#include <stdarg.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>
#include <stdlib.h>
#include <unistd.h>
#include <limits.h>


#define UNUSED(i) (void)(i)

#define BUFFER_SIZE 1024
#define BUFF_F -1

#define PARAMS_INIT {0, 0, 0, 0, 0, 0, 0, 0, 0, 0, 0}
#define NULL_STR "(NULL)"

#define CON_LOWER 1
#define CON_UNSIGN 2

/**
 * struct par - parameters struct
 * @unsign: 1-bit field for unsigned specifier
 * @plus_flag: 1-bit field for '+' flag
 * @space_flag: 1-bit field for ' ' flag
 * @hashtag_flag: 1-bit field for '#' flag
 * @zero_flag: 1-bit field for '0' flag
 * @plus_flag: 1-bit field for '-' flag
 * @h_modifier: 1-bit field for 'h' modifier
 * @l_modifier: 1-bit field for 'l' modifier
 * @pre: Stores precision value
 * @width: Stores width value
 * @reserved: Reserved field for alignment (to ensure a 4-byte size)
*/
typedef struct par {
	unsigned int unsign				: 1;

	unsigned int plus_flag			: 1;
	unsigned int space_flag			: 1;
	unsigned int hashtag_flag		: 1;
	unsigned int zero_flag			: 1;
	unsigned int minus_flag			: 1;

	unsigned int width;
	unsigned int percision;
	unsigned int reserved;

	unsigned int h_modifier			: 1;
	unsigned int l_modifier			: 1;
} par_t;

/**
 * struct spec - Struct op
 * @spec: format.
 * @f: function associated.
 */
typedef struct spec
{
	char *spec;
	int (*f)(va_list, par_t *);
}spec_t;

/*printf.c*/
int _printf(const char *format, ...);

/*print.func.c*/
int print_int(va_list ap, par_t *par);
int print_char(va_list ap, par_t *par);
int print_string(va_list ap, par_t *par);
int print_percent(va_list ap, par_t *par);
int print_S(va_list ap, par_t *par);

/*puts.c*/
int _puts(char *str);
int _putchar(int c);

/*simple_printers*/
int print_rot13(va_list ap, par_t *par);
int print_rev(va_list ap, par_t *par);
int print_from_to(char *start, char *stop, char *except);

/*specifier*/
int (*get_speci(char *s))(va_list ap, par_t *par);
int get_print_fun(char *s, va_list ap, par_t *par);
int get_modif(char *s, par_t *par);
int get_flag(char *s, par_t *par);
char *get_width(char *s, par_t *par, va_list ap);

/*number*/
char *convert(long int num, int base, int flag, par_t *par);
int print_unsign(va_list ap, par_t *par);
int print_addr(va_list ap, par_t *par);

/*convert number*/
int print_HEX(va_list ap, par_t *par);
int print_hex(va_list ap, par_t *par);
int print_oct(va_list ap, par_t *par);
int print_binary(va_list ap, par_t *par);

/*print number*/
int _strlen(char *s);
int _isdig(int c);
int print_num(char *str, par_t *par);
int print_num_r_shift(char *str, par_t *par);
int print_num_l_shift(char *str, par_t *par);

/*par.c*/
void init_par(par_t *par, va_list ap);

/*string.c*/
char *get_perci(char *p, par_t *par, va_list ap);

/*print_unknown*/
int print_unknown(va_list ap, par_t *par);

#endif
