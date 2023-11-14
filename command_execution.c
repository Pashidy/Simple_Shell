#include "shell.h"
#include <string.h>
#include <stdlib.h>
#include <unistd.h>
#include <stdio.h>

void process_input(char *input)
{
	char *token;
	char *args[100];

	int i = 0;
	token = strtok(input, " \t\n");

	while (token != NULL && i < 99)
	{
		args[i] = token;
		i++;
		token = strtok(NULL, " \t\n");
	}
	args[i] = NULL;

	if (execvp(args[0], args) == -1)
	{
		perror(args[0]); // Print the error using the command name
		exit(EXIT_FAILURE);
	}
}
