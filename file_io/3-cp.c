#include <fcntl.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

/**
 * close_fd - closes a file descriptor or exits with code 100 on failure
 * @fd: file descriptor to close
 */
void close_fd(int fd)
{
	if (close(fd) == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't close fd %d\n", fd);
		exit(100);
	}
}

/**
 * open_source - opens source file or exits with code 98
 * @filename: source filename
 *
 * Return: source file descriptor
 */
int open_source(const char *filename)
{
	int fd;

	fd = open(filename, O_RDONLY);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", filename);
		exit(98);
	}

	return (fd);
}

/**
 * open_dest - opens destination file or exits with code 99
 * @filename: destination filename
 * @fd_from: source file descriptor to close on failure
 *
 * Return: destination file descriptor
 */
int open_dest(const char *filename, int fd_from)
{
	int fd;

	fd = open(filename, O_CREAT | O_WRONLY | O_TRUNC, 0664);
	if (fd == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't write to %s\n", filename);
		close_fd(fd_from);
		exit(99);
	}

	return (fd);
}

/**
 * copy_data - copies data from one file descriptor to another
 * @fd_from: source file descriptor
 * @fd_to: destination file descriptor
 * @file_from: source filename
 * @file_to: destination filename
 */
void copy_data(int fd_from, int fd_to,
	const char *file_from, const char *file_to)
{
	ssize_t rcount, wcount;
	char buffer[1024];

	rcount = read(fd_from, buffer, 1024);
	while (rcount > 0)
	{
		wcount = write(fd_to, buffer, rcount);
		if (wcount != rcount)
		{
			dprintf(STDERR_FILENO, "Error: Can't write to %s\n", file_to);
			close_fd(fd_from);
			close_fd(fd_to);
			exit(99);
		}
		rcount = read(fd_from, buffer, 1024);
	}

	if (rcount == -1)
	{
		dprintf(STDERR_FILENO, "Error: Can't read from file %s\n", file_from);
		close_fd(fd_from);
		close_fd(fd_to);
		exit(98);
	}
}

/**
 * main - copies the content of one file to another file
 * @argc: argument count
 * @argv: argument vector
 *
 * Return: 0 on success
 */
int main(int argc, char *argv[])
{
	int fd_from, fd_to;

	if (argc != 3)
	{
		dprintf(STDERR_FILENO, "Usage: cp file_from file_to\n");
		exit(97);
	}

	fd_from = open_source(argv[1]);
	fd_to = open_dest(argv[2], fd_from);
	copy_data(fd_from, fd_to, argv[1], argv[2]);

	close_fd(fd_from);
	close_fd(fd_to);

	return (0);
}
