#include<stdio.h>

int main (void)
{
	int num, a, b, c = 1;

	printf("enter you number : ");
	scanf("%d", &num);

	for (a = 1; a = num; a++)
	{
		for (b = num; b <= num; b--)
		{
			if (b > 0)
			{
				printf("%d", b);
			}
			else
			{
				break;
			}
		}
		num--;
		printf("\n");
	}
}