#include<stdio.h>

int main (void)
{
	int num, a, b;

	printf("Enter your number : ");
	scanf("%d", &num);

	for (a = num; a > 0; a--)
	{
		for (b = num; b >= a; b--)
			{
				printf("%d", b);
			}
		printf("\n");
	}
}