#include<stdio.h>

int main (void){
	int n;
	int a = 0;
	int b = 0;

	printf("the number of elements in the array: ");
	scanf("%d", &n);

	int arr[n];

	while (a < n){
		printf("Enter element %d: ", a + 1);
		scanf("%d", &arr[a]);
		a++;
	}

	int max1 = arr[0];
	int max2 = arr[0];
	
	for (int i = 1; i < n; i++) {
		if (arr[i] > max1) {
			max2 = max1;
			max1 = arr[i];
		}else if (arr[i] > max2 && arr[i] != max1)
		{
			max2 = arr[i];
		}
		
	}
	printf("Second largest element: %d", max2);
}