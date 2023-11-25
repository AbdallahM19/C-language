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
* _strdup - duplicates a string
*
* @str: a string to be duplicated
*
* Return: pointer to the duplicated string
*/
char *_strdup( const char *str)
{
	int i;
	char *p;
	int length = strlen(str);
	if (str == NULL)
		return (NULL);
	p = malloc(length + 1 * sizeof(char));
	if (p == 0)
		return (NULL);
	for (i = 0; i < length; i++)
		p[i] = str[i];
	return (p);
}
/**
*_puts - print a string
*
*@cat: one string to be printed
*
* Return: Nothing
*/
void _puts(char *cat)
{
	int x;
	if (!cat)
		return;
	for (x = 0; cat[x] != '\0'; x++)
		_putchar(cat[x]);
}
/**
* _putchar - print one char
* 
* @cat: character to be printed
*
* Return: the character
*/
int _putchar(char cat)
{
	static int count;
	static char BUF[WRITE_BUF_SIZE];

	if (cat == BUF_FLUSH || count >= WRITE_BUF_SIZE)
	{
		write(1, BUF, count);
		count = 0;
	}
	if (cat != BUF_FLUSH)
		BUF[count++] = cat;
	return (1);
}


