#include "shell.h"

/**
 * print_string_stderr - Prints a string to stderr.
 * @str: The string to be printed.
 */
void print_string_stderr(char *str)
{
	int i = 0;

	if (!str)
		return;

	while (str[i] != '\0')
	{
	write_character_stderr(str[i]);
	i++;
	}
}

/**
 * write_character_stderr - Writes a character to stderr.
 * @c: The character to be written.
 *
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int write_character_stderr(char c)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(2, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	buf[i++] = c;

	return (1);
}


/**
 * write_character_to_fd - Writes a character to the given file descriptor.
 * @c: The character to be written.
 * @fd: The file descriptor to write to.
 *
 * Return: On success 1. On error, -1 is returned,
 * and errno is set appropriately.
 */
int write_character_to_fd(char c, int fd)
{
	static int i;
	static char buf[WRITE_BUF_SIZE];

	if (c == BUF_FLUSH || i >= WRITE_BUF_SIZE)
	{
		write(fd, buf, i);
		i = 0;
	}
	if (c != BUF_FLUSH)
	buf[i++] = c;

	return (1);
}

/**
 * print_string_to_fd - Prints a string to the given file descriptor.
 * @str: The string to be printed.
 * @fd: The file descriptor to write to.
 *
 * Return: The number of characters written.
 */
int print_string_to_fd(char *str, int fd)
{
	int count = 0;

	if (!str)
	return (0);

	while (*str)
	{
	count += write_character_to_fd(*str++, fd);
	}

	return (count);
}
