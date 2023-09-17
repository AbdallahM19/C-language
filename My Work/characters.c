#include<stdio.h>

int main (void)
{
	int a, b, c;

	printf("enter your number: ");
	scanf("%d", &c);

	for (a = c; a >= 1; a--)
	{
		for (b = 1; b <= a; b++)
		{
			printf("%c", b + 64);	
		}
		printf("\n");
	}
}