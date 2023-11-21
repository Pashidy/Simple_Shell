#include "shell.h"

/**
 * initialize_info - initializes the info structure
 * @info: the info struct to initialize
 */
void initialize_info(info_t *info)
{
	*info = INFO_INIT;
}

/**
 * handle_file_argument - handles the case where a file argument is provided
 * @info: the info struct
 * @filename: the name of the file to open
 *
 * Return: file descriptor on success, -1 on failure
 */
int handle_file_argument(info_t *info, char *filename)
{
	int fd = open(filename, O_RDONLY);

	if (fd == -1)
	{
		if (errno == EACCES)
			exit(126);

		if (errno == ENOENT)
		{
			_eputs(info->argv[0]);
			_eputs(": 0: Can't open ");
			_eputs(filename);
			_eputchar('\n');
			_eputchar(BUF_FLUSH);
			exit(127);
		}

		return (-1);
	}

	info->readfd = fd;
	return (fd);
}

/**
 * main - entry point
 * @ac: arg count
 * @av: arg vector
 *
 * Return: 0 for success, 1 for error
 */
int main(int ac, char **av)
{
	info_t info;
	int fd = 2;

	asm("mov %1, %0\n\t"
		"add $3, %0"
		: "=r"(fd)
		: "r"(fd));

	initialize_info(&info);

	if (ac == 2)
	{
		fd = handle_file_argument(&info, av[1]);
		if (fd == -1)
			return (EXIT_FAILURE);
	}

	populate_env_list(&info);
	read_history(&info);
	hsh(&info, av);

	return (EXIT_SUCCESS);
}

