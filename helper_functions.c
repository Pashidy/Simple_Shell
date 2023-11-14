#include "shell.h"
#include <unistd.h>

/**
 * read_input - Reads user input from stdin
 *
 * Return: Pointer to the input string
 */
char *read_input(void)
{
	char *input = NULL;
	size_t len = 0;
	const char prompt[] = "($) ";

	if (write(STDOUT_FILENO, prompt, sizeof(prompt) - 1) == -1)
	{
		perror("write");
		exit(EXIT_FAILURE);
	}

	if (getline(&input, &len, stdin) == -1)
	{
		perror("getline");
		exit(EXIT_FAILURE);
	}

	return input;
}

