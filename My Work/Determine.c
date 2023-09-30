#include<stdio.h>

int main (void){
	int num;

	printf("Enter the numeric score: ");
	scanf("%d", &num);

	if (num % 2 == 0)
		printf("The entered number is even.");
	else if (num % 2 != 0)
		printf("The entered number is odd.");
}