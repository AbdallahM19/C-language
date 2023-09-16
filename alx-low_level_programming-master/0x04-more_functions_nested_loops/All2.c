#include "main.h"
/**
 * print_triangle - prints a triangle, followed by a new line
 * @size: size of the triangle
 */
void print_triangle(int size)
{
	if (size <= 0)
	{
		_putchar('\n');
	}
	else
	{
		int high, base;

		for (high = 1; high <= size; high++)
		{
			for (base = high; base < size; base++)
			{
				_putchar(' ');
			}
			for (base = 1; base <= high; base++)
			{
				_putchar('#');
			}
			_putchar('\n');
		}
	}
}