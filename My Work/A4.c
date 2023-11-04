#include "main.h"

#define USAGE "Usage: cp file_from file_to\n"
#define ERROR_NOREAD "Error: Can't read from file %s\n"
#define ERROR_NOWRITE "Error: Can't write to %s\n"
#define ERROR_NOCLOSE "Error: Can't close fd %d\n"
#define PERMISSIONS (S_IRUSR | S_IWUSR | S_IRGRP | S_IWGRP | S_IROTH)

/**
 * main - Entry point,
 * copies the content of one file to another
 * @ac: Argument count
 * @av: Argument vector
 * Return: 0 on success,
 * exit codes as specified in the prompt on failure
 */
int main(int ac, char **av)
{
	int from_fd = 0, to_fd = 0;
	ssize_t a;
	char buf[BUF_SIZE];

	if (ac != 3)
		dprintf(STDERR_FILENO, USAGE), exit(97);
	from_fd = open(av[1], O_RDONLY);
	if (from_fd == -1)
		dprintf(STDERR_FILENO, ERROR_NOREAD, av[1]), exit(98);
	to_fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, PERMISSIONS);
	if (to_fd == -1)
		dprintf(STDERR_FILENO, ERROR_NOWRITE, av[2]), exit(99);
	while ((a = read(from_fd, buf, BUF_SIZE)) > 0)
		if (write(to_fd, buf, a) != a)
			dprintf(STDERR_FILENO, ERROR_NOWRITE, av[2]), exit(99);
	if (a == -1)
		dprintf(STDERR_FILENO, ERROR_NOWRITE, av[1]), exit(98);
	if (close(from_fd) == -1)
		dprintf(STDERR_FILENO, ERROR_NOCLOSE, from_fd), exit(100);
	if (close(to_fd) == -1)
		dprintf(STDERR_FILENO, ERROR_NOCLOSE, to_fd), exit(100);
	return (EXIT_SUCCESS);
}