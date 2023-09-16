#include"main.h"

/**
 * print_alphabet_x10 - function that will print the alphabet 10 times
 *
*/

void print_alphabet_x10(void)
{
	int line, char1;

	for (line = 0; line <= 9; line++)
	{
		for (char1 = 'a'; char1 <= 'z'; char1++)
			_putchar(char1);
		_putchar('\n');
	}
}
