#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <sys/types.h>

int main() {
	int num_children = 5;

	for (int i = 0; i < num_children; i++) {
		pid_t child_pid = fork();

		if (child_pid < 0) {
			perror("Fork failed");
			exit(1);
		} else if (child_pid == 0) {
			// This code is executed by the child process
			printf("Child %d executing ls -l /tmp:\n", i);

			// Execute the ls command using execve
			char* cmd = "ls";
			char* argv[] = {cmd, "-l", "/tmp", NULL};
			execve("/bin/ls", argv, NULL);

			// If execve fails, print an error message
			perror("Execve failed");
			exit(1);
		} else
		{
			int status;
			wait(&status);
		}
	}
	return (0);
}
