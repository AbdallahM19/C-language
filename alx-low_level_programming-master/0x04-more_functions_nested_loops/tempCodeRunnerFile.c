#include"main.h"

/**
 * more_numbers - print 0 - 14 (10) times
 * 
 * Return: Always 0 (Success)
*/

void more_numbers(void)
{
		int num, row, count;

		for (row = 0; row < 10; row++)
		{
			for (count = 0; count < 15; count++)
			{
				num = count;
				if (count > 9)
				{
					_putchar(1 + 48);
					num = count + 48;
				}
				_putchar(num + 48);
			}			
		_putchar('\n');
}