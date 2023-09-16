#include"main.h"

/**
 * main - Entry point
 *
 * Description: prints _putchar with main.h
 *
 * Return: Always 0 (Success)
*/

int main(void)
{
char str[] = "_putchar";
int char1;
for (char1 = 0; char1 < 8; char1++)
{
_putchar(str[char1]);
}
_putchar('\n');
return (0);
}
