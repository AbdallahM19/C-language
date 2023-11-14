void execute_command(char *command, int interactive)
{
	pid_t pid;
	char *args[READ_BUF_SIZE];
	int i = 0;

	char *token = strtok_custom(command, " \n");
	while (token != NULL && i < READ_BUF_SIZE - 1)
	{
		args[i++] = token;
		token = strtok_custom(NULL, " \n");
	}
	args[i] = NULL;

	if (args[0] == NULL)
	{
		return;
	}

	int pipe_found = 0;

	if (_strcmp(args[0], "exit") == 0)
	{
		if (interactive)
			exit(EXIT_SUCCESS);
	}

	if (_strcmp(args[0], "cd") == 0)
	{
		if (args[1] == NULL)
		{
			fprintf(stderr, "cd: missing argument\n");
			return;
		}
		if (chdir(args[1]) != 0)
		{
			perror("chdir");
		}

		return;
	}

	if (_strcmp(args[0], "pwd") == 0)
	{
		char cwd[READ_BUF_SIZE];
		if (getcwd(cwd, sizeof(cwd)) != NULL)
		{
			printf("%s\n", cwd);
		}
		else
		{
			perror("getcwd");
		}
		return;
	}

	for (i = 0; args[i] != NULL; ++i)
	{
		if (strcmp(args[i], "|") == 0)
		{
			args[i] = NULL;
			pipe_found = 1;
			break;
		}
	}

	pid = fork();
	if (pid < 0)
	{
		perror("fork");
		exit(EXIT_FAILURE);
	}
	else if (pid == 0)
	{
		if (pipe_found)
		{
			int pipe_fd[2];
			if (pipe(pipe_fd) == -1)
			{
				perror("pipe");
				exit(EXIT_FAILURE);
			}

			pid_t child_pid;
			child_pid = fork();
			if (child_pid == -1)
			{
				perror("fork");
				exit(EXIT_FAILURE);
			}
			else if (child_pid == 0)
			{
				close(pipe_fd[0]);
				dup2(pipe_fd[1], STDOUT_FILENO);
				close(pipe_fd[1]);

				execvp(args[0], args);
				perror("execvp");
				exit(EXIT_FAILURE);
			}
			else
			{
				close(pipe_fd[1]);
				waitpid(child_pid, NULL, 0);
				exit(EXIT_SUCCESS);
			}
		}
		else
		{
			execvp(args[0], args);
			perror("execvp");
			exit(EXIT_FAILURE);
		}
	}
	else
	{
		int status;
		if (interactive)
			waitpid(pid, &status, 0);
	}
}