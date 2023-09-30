#include <stdio.h>

int main (void){
	int num;

	printf("Enter the numeric score: ");
	scanf("%d", &num);

	if (num >= 90 && num <= 100)
		printf("Letter grade: A");
	else if (num >= 80 && num <= 89)
		printf("Letter grade: B");
	else if (num >= 70 && num <= 79)
		printf("Letter grade: C");
	else if (num >= 60 && num <= 69)
		printf("Letter grade: D");
	else if (num < 60)
		printf("Letter grade: Below 60");
//A: 90 - 100
//B: 80 - 89
//C: 70 - 79
//D: 60 - 69
//F: Below 60
}