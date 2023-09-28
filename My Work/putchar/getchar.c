#include <stdio.h>

int main() {
    char ch = 'A';

    putchar(ch); // Outputs 'A' to the console
    putchar('\n'); // Outputs a newline character
    
    puts("z"); //output z
    puts('z'); // error

    int ch1;

    printf("Enter a character: ");
    ch1 = getchar();

    printf("You entered: %c\n", ch1);

    return 0;
}