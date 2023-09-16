#include<stdio.h>

int main (void)
{
	int num, a, b;

	printf("Enter your number : ");
	scanf("%d", &num);

	for (a = 1; a <= num; a++)
	{
		
		for (b = num; b >= a; b--)
		{
			printf("%d", b);
		}
		printf("\n");
	}
}