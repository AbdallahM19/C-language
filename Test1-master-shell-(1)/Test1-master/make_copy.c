#include "shell.h"
/**
* _strcpy - copies a string
*
* @cat: first member
*
* @kitty: second one
*
* Return: cat
*/
char *_strcpy(char *cat, char *kitty)
{
	int x = 0;

	if (cat == kitty || kitty == 0)
		return (cat);
	for (; kitty[x] != '\0'; x++)
		cat[x] = kitty[x];
	cat[x] = '\0';
	return (cat);
}
/**
*_memset - fills memory with a constant byte
*
*@s: pointer to the area we will fill
*
*@b: char contain the data
*
*@n: uninsigned int to start with
*
*Return: (*S)
*/
char *_memset(char *s, char b, unsigned int n)
{
int i = 0;
	while (n > 0)
{
	s[i] = b;
	i++;
	n--;
}
	return (s);
}
/**
*_strncpy - copy string to another
*
*@cat: new string
*
*@kitty: the origin string
*
*@num: specific charachthers to copy
*
*Return: cat
*/
char *_strncpy(char *cat, char *kitty, int num)
{
	int x = 0, y = 0;

	for (; kitty[x] != '\0' && x < num-1; x++, y++)
		cat[y] = kitty[x];
	if (y < num)
	{
		for (; y < num; y++)
			cat[y] = '\0';
	}
	return (cat);
}

