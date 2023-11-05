#include <stdio.h>
#include<stdlib.h>

/**
 * main - prints the environment
 * Return: Always 0.
 */

extern char** environ;

int main(int argc, char *argv[], char *env[]) 
{
	for (char **env = environ; *env != NULL; env++)
		printf("%s\n", *env);

    printf("Address of env (main's third parameter): %p\n", (void *)env);
    printf("Address of environ (global variable): %p\n", (void *)environ);

    if (env == environ)
        printf("env and environ point to the same memory address.\n");
	else
        printf("env and environ are different.\n");
    return (0);
}