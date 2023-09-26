#include <stdio.h>

int main(void)
{
	int a, b, i = 0;
	int sum;
	int arr[a];

	printf("Enter the number of elements in the array: \n");
	scanf("%d", &a);
	while (b <= a){
		printf("Enter element: \n");
		scanf("%d: %d", &b, &a);
		arr[i] = b;
		i++;
	}
	sum = 0;
	printf("Sum of all elements: %d", sum);
	return 0;
}