#include"main.h"

/**
 * print_alphabet - utilizes on the _putchar function to print
 *                 the alphabet a - z
*/

void print_alphabet(void)
{
	int char1;

	for (char1 = 'a'; char1 <= 'z'; char1++)
		_putchar(char1);
	_putchar('\n');
}
