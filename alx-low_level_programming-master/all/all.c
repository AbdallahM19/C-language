#include"main.h"

/**
 * isASCII - print 32 / 126.
 * @a: int
 * Return: 1 / 0
 */

int isASCII(int a)
{
	return (a >= 32 && a <= 126);
}

/**
 * printf1 - printf1(char *b, int s1, int e1)
 * @b: string
 * @s1: start
 * @e1: end
 */

void printf1(char *b, int s1, int e1)
{
	int d = 0;

	while (d < 10)
	{
		if (d < e1)
			printf("%02x", *(b + s1 + d));
		else
			printf("  ");
		if (d % 2)
			printf(" ");
		d++;
	}
}

/**
 * printASCII -  prints a buffer.
 * @b: string
 * @s1: start
 * @e1: end
 */

void printASCII(char *b, int s1, int e1)
{
	int c1, i = 0;

	while (i < e1)
	{
		c1 = *(b + i + s1);
		if (!isASCII(c1))
			c1 = 46;
		printf("%c", c1);
		i++;
	}
}

/**
 * print_buffer -  prints a buffer.
 * @b: buffer
 * @size: size
 * Return: void
 */

void print_buffer(char *b, int size)
{
	int s1, e1;

	if (size > 0)
	{
		for (s1 = 0; s1 < size; s1 += 10)
		{
			e1 = (size - s1 < 10) ? size - s1 : 10;
			printf("%08x: ", s1);
			printf1(b, s1, e1);
			printASCII(b, s1, e1);
			printf("\n");
		}
	}
	else
		printf("\n");
}