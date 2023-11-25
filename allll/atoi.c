#include "shell.h"

/**
 * _atoi - simuilte atoi
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
*/
int _atoi(char *s)
{
	int i, sign = 1, f = 0, out;
	unsigned int res = 0;

	for (i = 0;  s[i] != '\0' && f != 2; i++)
	{
		if (s[i] == '-')
			sign *= -1;

		if (s[i] >= '0' && s[i] <= '9')
		{
			f = 1;
			res *= 10;
			res += (s[i] - '0');
		}
		else if (f == 1)
			f = 2;
	}
	if (sign == -1)
		out = -res;
	else
		out = res;
	return (out);
}

/**
 * interactive - check if it works in interactve mode
 * @info: struct address
 * Return: 1 or 0
*/
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks if character is a delimeter
 * @s: first member
 * @d: secooned one
 * Return: 1 or 0
*/
int is_delim(char s, char *d)
{
	while (*d)
	{
		if (*d == s)
			return (1);
		d++;
	}
	return (0);
}

/**
 * _isalpha- test if it is char
 * @s: a char
 * Return: 1 or 0
*/
int _isalpha(int s)
{
	if ((s >= 'a' && s <= 'z') || (s >= 'A' && s <= 'Z'))
		return (1);
	else
		return (0);
}