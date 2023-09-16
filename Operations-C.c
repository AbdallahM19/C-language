#include <stdio.h>

/**
 * main - Entry point
 *
 * Description: enter your numbers for:
 *              addition
 *              Subtraction
 *              multiplication
 *              Division 
 *
 * Return: Always 0 (Succesful)
*/

int main(void) {
    int num1, num2;
    printf("Enter your numbers: ");
    scanf("%d %d", &num1, &num2);
    printf("Addition: %d\n", (num1 + num2));
    printf("Subtraction: %d\n", (num1 - num2));
    printf("Multiplication: %d\n", (num1 * num2));
    if (num1 != 0) {
        printf("Division num 1: %d\n", (num1 / num2));
    }
    else {
        printf("Division num 1 by zero is not allowed.\n");
    }
    if (num2 != 0) {
        printf("Division num 2: %d\n", (num2 / num1));
    }
    else {
        printf("Division num 2 by zero is not allowed.\n");
    }
    return 0;
}
