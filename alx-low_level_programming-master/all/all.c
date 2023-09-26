#include <stdio.h>

int main(void){
	int a, b, i = 0, j;
	int sum = 0;
	

	printf("Enter the number of elements in the array: ");
	scanf("%d", &a);
	
	int arr[a];

	while (i < a){
		printf("Enter element %d: ", i + 1);
		scanf("%d", &b);
		arr[i] = b;
		i++;
	}

	j = 0;
	while (j < a){
		sum += arr[j];
		j++;
	}

	printf("Sum of all elements: %d\n", sum);

	return 0;
}