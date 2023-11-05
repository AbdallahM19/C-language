#include <stdio.h>
#include<stdlib.h>
#include <string.h>
extern char** environ;

char *_getenv(const char *name)
{
    for (int i = 0; environ[i] != NULL; i++)
    {
        if (strncmp(environ[i], name, strlen(name)) == 0)
            return (&environ[i][strlen(name) + 1]);
        else
            return (NULL);
    }
}
/**
 * main - prints the environment
 * Return: Always 0.
 */


int main(int argc, char *argv[], char *env[]) 
{
    const char *name = "PATH";
    char *result = getenv(name);
    char *delim = ":";
    char *token = strtok(result, ":");
    while (token != NULL)
    {
        printf ("%s\n", token);
        token = strtok(NULL, delim);
    }
    
    for (char **env = environ; *env != NULL; env++)
		printf("%s\n", *env);

    printf("Address of env (main's third parameter): %p\n", (void *)env);
    printf("Address of environ (global variable): %p\n", (void *)environ);

    if (env == environ)
        printf("env and environ point to the same memory address.\n");
	else
        printf("env and environ are different.\n");
    if (result != NULL) {
        printf("%s=%s\n", name, result);
    } else {
        printf("%s not found\n", name);
    }
    return (0);
}