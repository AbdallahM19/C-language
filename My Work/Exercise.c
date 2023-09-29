#include <stdio.h>

// Define a recursive function to calculate the factorial
int factorial(int n) {
    // Base case: factorial of 0 or 1 is 1
    if (n == 0 || n == 1) {
        return 1;
    }
    // Recursive case: factorial of n is n times factorial of (n-1)
    else {
        return n * factorial(n - 1);
    }
}

int main() {
    int num = 5; // Example input
    int result = factorial(num); // Call the recursive function
    printf("Factorial of %d is %d\n", num, result);
    return 0;
}