#include"main.h"

/**
 * main - Entry point
 *
 * Description: prints the first 50 Fibonacci numbers
 *		starting with 1 and 2
 *		and end with a new line
 *
 * Return: Always 0 (Success)
*/

int main(void)
{
	int count;
	unsigned long fib = 0, fib2 = 1, sum;

	for (count = 0; count < 50; count++)
	{
		sum = fib + fib2;
		printf("%lu", sum);

		fib = fib2;
		fib2 = sum;

		if (count == 49)
			printf("\n");
		else
			printf(", ");
	}

	return (0);
}
