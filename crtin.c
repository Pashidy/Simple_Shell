#include "shell.h"

/**
 * exit_shell - Exits the shell.
 * @info: Structure containing arguments.
 * Return: -2 to signal exit.
 */
int exit_shell(info_t *info)
{
	int exit_code;

	if (info->argv[1])
	{
		exit_code = _erratoi(info->argv[1]);
		if (exit_code == -1)
		{
			info->status = 2;
			print_error(info, "Illegal number: ");
			_eputs(info->argv[1]);
			_eputchar('\n');
			return (1);
		}
		info->err_num = exit_code;
		return (-2);
	}

	info->err_num = -1;
	return (-2);
}

/**
 * change_directory - Changes the current directory.
 * @info: Structure containing arguments.
 * Return: 0 on success, 1 on failure.
 */
int change_directory(info_t *info);
int change_directory(info_t *info)
{
	char *current_dir, *new_dir, buffer[1024];
	int chdir_ret;

	current_dir = getcwd(buffer, 1024);
	if (!current_dir)
		_puts("TODO: >>getcwd failure emsg here<<\n");

	if (!info->argv[1])
	{
		new_dir = _getenv(info, "HOME=");
		if (!new_dir)
			chdir_ret = chdir((new_dir = _getenv(info, "PWD=")) ? new_dir : "/");
		else
			chdir_ret = chdir(new_dir);
	}
	else if (_strcmp(info->argv[1], "-") == 0)
	{
		if (!_getenv(info, "OLDPWD="))
		{
			_puts(current_dir);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(info, "OLDPWD=")), _putchar('\n');
		chdir_ret = chdir((new_dir = _getenv(info, "OLDPWD=")) ? new_dir : "/");
	}
	else
		chdir_ret = chdir(info->argv[1]);

	if (chdir_ret == -1)
	{
		print_error(info, "can't cd to ");
		_eputs(info->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(info, "OLDPWD", _getenv(info, "PWD="));
		_setenv(info, "PWD", getcwd(buffer, 1024));
	}

	return (0);
}

/**
 * display_help - Displays help information.
 * @info: Structure containing arguments.
 * Return: Always 0.
 */
int display_help(info_t *info)
{
	char **arg_array;

	arg_array = info->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_array); /* temp att_unused workaround */
	return (0);
}

/**
 * for_loop_shell_builtins - Calls each shell built-in function in a for loop.
 * @info: Structure containing arguments.
 * Return: Always 0.
 */
int for_loop_shell_builtins(info_t *info)
{
	int (*shell_builtins[])(info_t *) = {exit_shell,
		change_directory, display_help};
	int num_builtins = sizeof(shell_builtins) / sizeof(shell_builtins[0]);
	int i;

	for (i = 0; i < num_builtins; i++)
	{
		if (shell_builtins[i](info) == -2)
			return (-2);
	}

	return (0);
}
