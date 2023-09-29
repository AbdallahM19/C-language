#include"main.h"

int sqrt(int n, int sum);

/**
 * _sqrt_recursion - returns the natural square root
 * @n: number to calculate the square root
 * Return: square root
*/

int _sqrt_recursion(int n)
{
	if (n < 0)
		return (-1);
	return (sqrt(n, 0));
}

/**
 * sqrt - find sqrt root
 * @n: number to calculate the sqaure root of
 * @sum: iterator
 * Return: square root
*/

int sqrt(int n, int sum)
{
	if (sum * sum > n)
		return (-1);
	if (sum * sum == n)
		return (sum);
	return (sqrt(n, sum + 1));
}