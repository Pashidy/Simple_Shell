#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @info: Pointer to the information structure.
 *
 * Return: 1 if the exit command has an argument,
 * -2 if successful, 0 otherwise.
 */
int exit_shell(info_t *info)
{
	int exit_check;
	int i = 1;

	while (info->argv[i])
	{
	exit_check = custom_atoi(info->argv[i]);
	if (exit_check != -1)
	{
		info->err_num = exit_check;
		return (-2);
	}
		i++;
	}

	info->err_num = -1;
	return (-2);
}

/**
 * get_current_directory - Gets the current working directory.
 * @buffer: Buffer to store the current directory.
 *
 * Return: A pointer to the buffer containing the current directory.
 */
char *get_current_directory(char *buffer)
{
	char *current_directory = getcwd(buffer, 1024);

	if (!current_directory)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	return (current_directory);
}

/**
 * change_directory - Changes the current directory.
 * @info: Pointer to the information structure.
 *
 * Return: 0 on success, 1 if unable to find directory,
 * -1 on chdir failure.
 */
int change_directory(info_t *info)
{
	char buffer[1024];
	char *current_directory = get_current_directory(buffer);
	char *new_directory;

	if (!info->argv[1])
	{
		new_directory = _getenv(info, "HOME=");
	if (!new_directory)
		new_directory = _getenv(info, "PWD=");
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
	if (!_getenv(info, "OLDPWD="))
	{
		_puts(current_directory);
		_putchar('\n');
	return (1);
	}
		_puts(_getenv(info, "OLDPWD="));
		_putchar('\n');
		new_directory = _getenv(info, "OLDPWD=");
	}
	else
	{
		new_directory = info->argv[1];
	}

	if (chdir(new_directory) == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]);
		_eputchar('\n');
	return (-1);
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", get_current_directory(buffer));
	return (0);
	}
}

/**
 * help_command - Displays help information.
 * @info: Pointer to the information structure.
 *
 * Return: Always 0.
 */
int help_command(info_t *info)
{
	(void)info;
	_puts("help call works. Function not yet implemented \n");
	return (0);
}
