#include "main.h"
#include <fcntl.h>
#include <unistd.h>

/**
 * create_file - creates a file
 * @filename: name of file to create
 * @text_content: NULL terminated string to write
 *
 * Return: 1 on success, -1 on failure
 */
int create_file(const char *filename, char *text_content)
{
	int fd;
	ssize_t bytes_written;
	size_t len = 0;

	if (filename == NULL)
		return (-1);

	while (text_content != NULL && text_content[len] != '\0')
		len++;

	fd = open(filename, O_WRONLY | O_CREAT | O_TRUNC, 0600);
	if (fd == -1)
		return (-1);

	bytes_written = write(fd, text_content, len);
	if (bytes_written == -1 || (size_t)bytes_written != len)
	{
		close(fd);
		return (-1);
	}

	close(fd);
	return (1);
}
