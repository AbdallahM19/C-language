int main(int argc, char **argv)
{
	struct_t argument[] = { ARGU_INIT };
	int status = 0;
	char *line = NULL;
	size_t len = 0;

	(void)argc;

	populate_env_list(argument);
	history_reading(argument);

	while (1)
	{
		if (isatty(STDIN_FILENO))
			write(STDOUT_FILENO, "$ ", 2);  // Print the prompt if input is from a terminal

		if (getline(&line, &len, stdin) == -1)
		{
			perror("getline");
			break;
		}

		init_argument(argument, argv);
		status = execute_command(argument, line);

		if (status == -1)
			command_placeholder(argument);

		free_argument(argument, 0);
		free(line);
		line = NULL;
		len = 0;
	}

	history_writing(argument);
	free_argument(argument, 1);

	return (status);
}