#include<stdio.h>

int main (void)
{
	int a, b, c;

	printf("enter your number: ");
	scanf("%d", &c);

	for (a = 1; a <= c; a++)
	{
		for (b = 1; b <= a; b++)
		{
			printf("%c", a + 64);	
		}
		printf("\n");
	}
}