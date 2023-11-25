#include "shell.h"

/**
 * _strncpy - copy string to another
 * @dest: new string
 * @src: the origin string
 * @n: specific charachthers to copy
 * Return: cat
*/
char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *str = dest;

	for (i = 0; src[i] != '\0' && i < n - 1; i++)
		dest[i] = src[i];
	if (i < n)
	{
		for (j = i; j < n; j++)
			dest[j] = '\0';
	}
	return (str);
}

/**
 * _strncat - concatenates two strings
 * @dest: new string
 * @src: the origin strin
 * @n: interger
 * Return: cat
*/
char *_strncat(char *dest, char *src, int n)
{
	int i = 0, j = 0;
	char *str = dest;

	while (dest[i] != '\0')
		i++;
	while (src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++, j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (str);
}

/**
 * _strchr - find specific characther in string
 * @s: the string
 * @c: the char
 * Return: the pointer or NULL
*/
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');
	return (NULL);
}
