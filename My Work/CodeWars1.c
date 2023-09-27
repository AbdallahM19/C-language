#include <stdio.h>

void two_oldest_ages(size_t n, const int ages[n], int result[2]) {
	int max1 = ages[0];
	int max2 = ages[1];

	if (max1 < max2) {
		int temp = max1;
		max1 = max2;
		max2 = temp;
	}

	for (size_t i = 2; i < n; i++) {
		if (ages[i] > max1) {
			max2 = max1;
			max1 = ages[i];
		} else if (ages[i] > max2) {
			max2 = ages[i];
		}
	}

	result[0] = max2;
	result[1] = max1;
}

int main() {
	int ages1[] = {1, 2, 10, 8};
	int result1[2];
	two_oldest_ages(4, ages1, result1);
	printf("[%d, %d]\n", result1[0], result1[1]);  // Output: [8, 10]

	int ages2[] = {1, 5, 87, 45, 8, 8};
	int result2[2];
	two_oldest_ages(6, ages2, result2);
	printf("[%d, %d]\n", result2[0], result2[1]);  // Output: [45, 87]

	int ages3[] = {1, 3, 10, 0};
	int result3[2];
	two_oldest_ages(4, ages3, result3);
	printf("[%d, %d]\n", result3[0], result3[1]);  // Output: [3, 10]

	return 0;
}