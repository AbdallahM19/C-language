#include "shell.h"

/**
 * _strlen - calculate the length of a string
 * @s: string to be checked
 * Return: the count
*/
int _strlen(char *s)
{
	int i = 0;

	if (!s)
		return (0);
	for (i = 0; *s++; i++)
		;
	return (i);
}

/**
 * _strcmp - compare two strings
 * @s1: first member
 * @s2: seconed one
 * Return: the result
*/
int _strcmp(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
		if (*s1 != *s2)
			return (*s1 - *s2);
		s1++;
		s2++;
	}
	if (*s1 == *s2)
		return (0);
	else
		return (*s1 < *s2 ? -1 : 1);
}

/**
 * starts_with - checks if specific word start with specific char
 * @haystack: first member
 * @needle: seconed one
 * Return: pointer
*/
char *starts_with(const char *haystack, const char *needle)
{
	while (*needle)
		if (*needle++ != *haystack++)
			return (NULL);
	return ((char *)haystack);
}

/**
 * _strcat - concatenates two strings
 * @dest: first member
 * @src: tsecond one
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	char *ret = dest;

	while (*dest)
		dest++;
	while (*src)
		*dest++ = *src++;
	*dest = *src;
	return (ret);
}