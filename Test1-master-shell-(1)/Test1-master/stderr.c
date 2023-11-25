#include "shell.h"
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
	static char buf[BUFFER_WR];
	if (ch == NEGATTIVE || i >= BUFFER_WR)
	{
		write(2, buf, i);
		i = 0;
	}
	if (ch != NEGATTIVE)
		buf[i++] = ch;
	return (1);
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
* print_error - print error massage to stderr
*
* @argument: pointer to the struct
*
* @string: string to be printed
*
* Return: void
*/
void print_error(struct_t *argument, char *string)
{
	_eputs(argument->fname);
	_eputs(": ");
	print_integer(argument->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(argument->argv[0]);
	_eputs(": ");
	_eputs(string);
}