#include<stdio.h>

int main (void)
{
	int a, b, c, d;

	printf("enter your number: ");
	scanf("%d", &c);

	for (a = 1; a <= c; a++)
	{
		for (b = 1; b <= a; b++)
		{
			printf("*");	
		}
		printf("\n");
	}
	for (a = c - 1; a >= 1; a--)
	{
		for (b = 1; b <= a; b++)
		{
			printf("*");
			
		}
		printf("\n");
	}
}