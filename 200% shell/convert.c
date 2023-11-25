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
	if (!(flag & CONVERT_UNSIGNED) && n < 0)
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
 * list_to_strings - convert a list to string
 *
 * @h: pointer to the list
 *
 * Return: array
 */
char **list_to_strings(list_t *h)
{
	list_t *cat = h;
	size_t x = list_length(h), y;
	char **strs;
	char *str;

	if (!h || !x)
		return (NULL);
	strs = malloc(sizeof(char *) * (x + 1));
	if (!strs)
		return (NULL);
	for (x = 0; cat; cat = cat->next, x++)
	{
		str = malloc(strlen(cat->string) + 1);
		if (!str)
		{
			for (y = 0; y < x; y++)
				free(strs[y]);
			free(strs);
			return (NULL);
		}
		str = strcpy(str, cat->string);
		strs[x] = str;
	}
	strs[x] = NULL;
	return (strs);
}
