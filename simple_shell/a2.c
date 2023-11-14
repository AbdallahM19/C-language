#include <stdio.h>
#include <unistd.h>
#include <sys/types.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <stdarg.h>
#include <stdlib.h>

int main()
{
	pid_t pid;
	char *argv[] = {"/bin/ls", "-la"};

	pid = fork();

	if (pid == -1)
	{
		return -1;
	}
	else if (pid == 0)
	{
		execve(argv[0], argv, NULL);
	}
	else
	{
		wait(NULL);
	}
	return 0;
}