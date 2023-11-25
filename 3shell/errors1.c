#include "shell.h"
/**
* convert_number - convert a number
* 
* @n: number
*
* @base: base
*
* @flag: argument flags
*
* Return: a string
*/
char *convert_number(long int n, int base, int flag)
{
	static char *array;
	static char buf[50];
	char sign = 0, *p;
	unsigned long num = n;
	if (!(flag & CONVERT_UNSIGNED) && n< 0)
	{
		num = -n;
		sign = '-';
	}
	array = flag & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	p = &buf[49];
	*p = '\0';
	do	{
		*--p = array[num % base];
		num /= base;
	} while (num != 0);

	if (sign)
		*--p = sign;
	return (p);
}
/**
* convert_string - convert a string to an integer
*
* @string: the only member
*
* Return: result or -1
*/
int convert_string(char *string)
{
	int i = 0;
	unsigned long int result = 0;
	if (*string == '+')
		string++;
	for (i = 0;  string[i] != '\0'; i++)
	{
		if (string[i] >= '0' && string[i] <= '9')
		{
			result *= 10;
			result += (string[i] - '0');
			if (result > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (result);
}
/**
* print_integer - print an integer to a filedescriptor 
* 
* @num: number
* 
* @file: tfile
*
* Return: character
*/
int print_integer(int num, int file)
{
	int (*__putchar)(char) = _putchar;
	int i, count = 0;
	unsigned int _abs_, current;

	if (file == STDERR_FILENO)
		__putchar = _eputchar;
	if (num < 0)
	{
		_abs_ = -num;
		__putchar('-');
		count++;
	}
	else
		_abs_ = num;
	current = _abs_;
	for (i = 1000000000; i > 1; i /= 10)
	{
		if (_abs_ / i)
		{
			__putchar('0' + current / i);
			count++;
		}
		current %= i;
	}
	__putchar('0' + current);
	count++;

	return (count);
}
/**
 * remove_comments - removecoments
 * 
 * @cat: pointer
 *
 * Return: Always 0;
 */
void remove_comments(char *cat)
{
	int x;
	for (x = 0; cat[x] != '\0'; x++)
		if (cat[x] == '#' && (!x || cat[x - 1] == ' '))
		{
			cat[x] = '\0';
			break;
		}
}
