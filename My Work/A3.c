#include "main.h"

#define BUF_SIZE 1024

/**
 * print_error - print to STDERR_FILENO
 * @message: message to print
 */
void print_error(const char *message)
{
	dprintf(STDERR_FILENO, "%s\n", message);
}

/**
 * copy_file - copy the content of one file to another
 * @file_from: source file descriptor
 * @file_to: destination file descriptor
 * @name_from: source file name
 * @name_to: destination file name
 * Return: 0 on success, exit codes on failure
 */
int copy_file(int file_from, int file_to,
const char *name_from, const char *name_to)
{
	ssize_t bytes_read, bytes_written;
	char buffer[BUF_SIZE];

	while ((bytes_read = read(file_from, buffer, BUF_SIZE)) > 0)
	{
		bytes_written = write(file_to, buffer, bytes_read);
		if (bytes_written == -1)
		{
			print_error("Error: Can't write to file");
			return (99);
		}
	}
	if (bytes_read == -1)
	{
		print_error("Error: Can't read from file");
		return (98);
	}
	if (close(file_from) == -1)
	{
		print_error("Error: Can't close file descriptor");
		return (100);
	}
	if (close(file_to) == -1)
	{
		print_error("Error: Can't close file descriptor");
		return (100);
	}
	return (0);
}

/**
 * main - Entry point, copies the content of one file to another
 * @ac: Argument count
 * @av: Argument vector
 * Return: 0 on success, exit codes as specified in the prompt on failure
 */
int main(int ac, char *av[])
{
	int from_fd, to_fd;
	struct stat st;

	if (ac != 3)
	{
		print_error("Usage: cp file_from file_to");
		return (97);
	}
	from_fd = open(av[1], O_RDONLY);
	if (from_fd == -1)
	{
		print_error("Error: Can't read from file");
		return (98);
	}
	if (fstat(from_fd, &st) == -1)
	{
		print_error("Error: Can't get file status");
		return (98);
	}
	to_fd = open(av[2], O_WRONLY | O_CREAT | O_TRUNC, st.st_mode);
	if (to_fd == -1)
	{
		print_error("Error: Can't write to file");
		return (99);
	}
	int result = copy_file(from_fd, to_fd, av[1], av[2]);

	return (result);
}