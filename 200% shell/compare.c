#include "shell.h"
/**
 * _strcat - concatenates two strings
 * @dest: first member
 * @src: tsecond one
 * Return: dest
 */
char *_strcat(char *dest, char *src)
{
	int i = 0, j = 0;

	while (dest[j] != '\0')
		j++;
	while (src[i] != '\0')
	{
		dest[j] = src[i];
		j++;
		i++;
	}
	dest[j] = '\0';
	return (dest);
}
/**
 * _strcmp - compare two strings
 * @s1: first member
 * @s2: seconed one
 * Return: the result
*/
int _strcmp(char *s1, char *s2)
{
	int i;
	int result = 0;

	for (i = 0; s1[i] != '\0' && result == 0; i++)
	{
		result = s1[i] - s2[i];
	}
	return (result);
}
/**
 * _strncat - concatenates two strings
 * @cat: new string
 * @kitty: the origin strin
 * @num: interger
 * Return: cat
*/
char *_strncat(char *cat, char *kitty, int num)
{
	int i, j;

	for (i = 0; kitty[i] != '\0'; i++)
		;
	for (j = 0; cat[j] != 0 && j < num; j++)
		kitty[i + j] = cat[j];
	if (j < num)
		kitty[j] = '\0';
	return (kitty);
}
