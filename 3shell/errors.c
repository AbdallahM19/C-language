#include "shell.h"
/**
* print_error - print error massage to stderr
*
* @info: pointer to the struct
*
* @string: string to be printed
*
* Return: void
*/
void print_error(info_t *info, char *string)
{
	_eputs(info->fname);
	_eputs(": ");
	print_integer(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(string);
}
/**
*_eputs - print a string to stderr
*
* @cat: ta string
*
* Return: void
*/
void _eputs(char *cat)
{
	int i;
	if (!cat)
		return;
	for (i = 0; cat[i] != '\0'; i++)
		_eputchar(cat[i]);
}
/**
 * _eputchar - print a char to stderr
 * 
 * @ch: a char
 *
 * Return: the char
 */
int _eputchar(char ch)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];
	if (ch == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != BUF_FLUSH)
		buf[i++] = ch;
	return (1);
}
/**
* _putfd - print a char to a filedescriptor
* @ch: a character
*
* @fd: a filedescriptor
*
* Return: the char
*/
int _putfd(char ch, int file)
{
	static int x;
	static char buf[WRITE_BUF_SIZE];
	if (ch == BUF_FLUSH || x >= WRITE_BUF_SIZE)
	{
		write(file, buf, x);
		x = 0;
	}
	if (ch != BUF_FLUSH)
		buf[x++] = ch;
	return (1);
}
/**
*_putsfd - print a string to a filedescriptor
*
* @cat: a string
*
* @fd: the filedescriptor to write to
*
* Return: the number of chars put
*/
int _putsfd(char *cat, int file)
{
int x = 0;
	if (!cat)
		return (0);
	while (*cat)
	{
		x += _putfd(*cat++, file);
	}
	return (x);
}
