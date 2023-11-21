#include "shell.h"

/**
 * tokenize_input - Tokenizes the input string and stores
 * tokens in an array.
 * @input: Input string to be tokenized.
 * @args: Array to store tokens.
 * Return: Number of tokens.
 */
int tokenize_input(char *input, char *args[])
{
	char *token;
	int count = 0;

	token = strtok(input, " \t\n");

	for (; token != NULL && count < MAX_ARGS - 1; token = strtok(NULL, " \t\n"))
	{
		args[count++] = token;
	}

	args[count] = NULL;
	return (count);
}

/**
 * execute_command - Executes a command with arguments.
 * @args: Array containing command and arguments.
 * Return: 0 on success
 */
void execute_command(char *args[])
{
	if (execvp(args[0], args) == -1)
	{
	perror(args[0]);
	exit(EXIT_FAILURE);
	}
}

/**
 * process_input - Parses and executes a command from
 * the input string using execvp.
 * @input: Input string containing the command.
 */
void process_input(char *input)
{
	char *args[MAX_ARGS];
	int arg_count = tokenize_input(input, args);

	if (arg_count > 0)
	{
	execute_command(args);
	}
}

/**
 * main - entry point
 *
 * Return: 0 (always)
 */
int main(void)
{
	char *input;
	size_t len = 0;

	while (1)
	{
	printf("($) ");

	if (getline(&input, &len, stdin) == -1)
	{
	perror("getline");
	exit(EXIT_FAILURE);
	}
	process_input(input);
	free(input);
	}
	return (0);
}
