#include<stdio.h>

int main(void)
{
    int a, b, sum, x;

    x = scanf("%d\n", &a, &b);
    printf("X = %d\n", x);

    x = scanf("%d %d\n", &a, &b);
    printf("X = %d\n", x);

    x = scanf("%d %d %d\n", &a, &b, &sum);
    printf("X = %d\n", x);
    return 0;
}
