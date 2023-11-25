#include "shell.h"
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
	static char BUF[BUFFER_WR];

	if (cat == NEGATTIVE || count >= BUFFER_WR)
	{
		write(1, BUF, count);
		count = 0;
	}
	if (cat != NEGATTIVE)
		BUF[count++] = cat;
	return (1);
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
 * print_list - print the element of a list
 *
 * @head: pointer to list
 *
 * Return: the list
 */
size_t print_list(const list_t *head)
{
size_t count = 0;
	while (head)
{
		_puts(convert_number(head->n, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		count++;
}
	return (count);
}
/**
 * print_list_str - print specific element
 *
 * @head: pointer to first node
 *
 * Return: the list
 */
size_t print_list_str(const list_t *head)
{
size_t x = 0;
	while (head)
	{
		_puts(head->string ? head->string : "(nil)");
		_puts("\n");
		head = head->next;
		x++;
	}
	return (x);
}
