#include<stdio.h>

int main (void)
{
	int a, b, c;

	printf("enter your number: ");
	scanf("%d", &c);

	for (a = c; a >= 1; a--)
	{
		for (b = 65; b < a + 65; b++)
		{
			printf("%c", b);	
		}
		printf("\n");
	}
}