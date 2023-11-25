#include<stdio.h>
#include<stdlib.h>
#include<stdbool.h>
#include<string.h>

char *strrev (char *string)
{
	char tab;
	int i, j;
	for (i = 0, j = strlen(string) - 1; i < j; i++, j--)
	{
		tab = string[i];
		string[i] = string[j];
		string[j] = tab;
	}
	return (string); // reverse the string in place and return it
}

int main()
{
    char str[] = "world";
    strrev(str);
    printf("%s", str);
    return 0;
}