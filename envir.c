#include "shell.h"

/**
 * display_environment - Displays the current environment.
 * @environment: Environment list.
 * Return: 0
 */
void display_environment(list_t *environment)
{
	print_list_str(environment);
	return (0);
}

/**
 * find_environment_variable - Finds the value of an
 * environment variable.
 *
 * @environment: Environment list.
 * @name: Environment variable name.
 * Return: The value of the environment variable.
 */
char *find_environment_variable(list_t *environment, const char *name)
{
	list_t *current_node = environment;
	char *value;

	while (current_node)
	{
	value = starts_with(current_node->str, name);
	if (value && *value)
		return (value);
		current_node = current_node->next;
	}

	return (NULL);
}

/**
 * initialize_environment_variable - Initializes a new environment
 * variable or modifies an existing one.
 *
 * @info: Structure containing potential arguments.
 * Return: 0 on success, 1 on error.
 */
int initialize_environment_variable(info_t *info)
{
	if (info->argc != 3)
	{
	display_error("Incorrect number of arguments\n");
	return (1);
	}

	if (update_environment_variable(info->argv[1], info->argv[2]) == 0)
	return (1);

	return (0);
}

/**
 * delete_environment_variable - Deletes an environment variable.
 * @info: Structure containing potential arguments.
 *
 * Return: 0 on success, 1 on error.
 */
int delete_environment_variable(info_t *info)
{
	int x = 1;

	if (info->argc == 1)
	{
		display_error("Too few arguments.\n");
		return (1);
	}

	while (x <= info->argc)
	{
		unset_environment_variable(info->argv[x]);
		x++;
	}

	return (0);
}
