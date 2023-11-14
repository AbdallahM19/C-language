#include "shell.h"

/**
 * _strncpy - Write a function that copies a string.
 * @dest: pointer to destination input buffer
 * @src: pointer to source input buffer
 * @n: bytes of @src
 * Return: pointer to resulting string @dest
*/

char *_strncpy(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	while (src[i] != '\0' && i < n - 1)
	{
		dest[i] = src[i];
		i++;
	}
	if (i < n)
	{
		j = i;
		while ( j < n)
		{
			dest[j] = '\0';
			j++;
		}
	}
	return (s);
}

/**
 * _strncat - Write a function that concatenates two strings.
 * @dest: pointer to destnation input
 * @src: pointer to source input
 * @n: most number of bytes from @src
 * Return: pointer to resulting string @dest
*/

char *_strncat(char *dest, char *src, int n)
{
	int i, j;
	char *s = dest;

	i = 0;
	j = 0;
	while(dest[i] != '\0')
		i++;
	while(src[j] != '\0' && j < n)
	{
		dest[i] = src[j];
		i++;
		j++;
	}
	if (j < n)
		dest[i] = '\0';
	return (s);
}

/**
 * _strchr - Write a function that locates a character in a string.
 * @s: pointer
 * @c: char
 * Return: a pointer to the first occurrence of the character c
 *          or NULL if char not found
*/

char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}