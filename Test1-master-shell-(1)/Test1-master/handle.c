#include "shell.h"
/**
 * handle_sign - handle ctrl-C
 * 
 * @sig: void integer
 *
 * Return: void
 */
void handle_sign(int sig)
{
	(void) sig;
	_puts("\n");
	_puts("$ ");
	_putchar(NEGATTIVE);
}