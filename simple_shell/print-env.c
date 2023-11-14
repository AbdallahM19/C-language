#include "shell.h"

void print_env(char **env)
{
	size_t i;

	for (i = 0; env[i]; i++)
		printf("%s\n", env[i]);
}