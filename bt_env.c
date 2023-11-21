#include "shell.h"

/**
 * my_env - prints the current environ
 * @inf: struct containing potential arguments
 * used to maintain constant function prototype.
 * Return: 0
 */
int my_env(info_t *inf)
{
	print_list_str(inf->env);
	return (0);
}

/**
 * get_env - gets the value of an environ variable
 * @inf: struct containing potential arguments.
 * @nam: env variable name
 *
 * Return: value
 */
char *get_env(info_t *inf, const char *nam)
{
	list_t *nod = inf->env;
	char *p;

	while (nod)
	{
		p = starts_with(nod->str, nam);
		if (p && *p)
			return (p);
		nod = nod->next;
	}
	return (NULL);
}

/**
 * my_setenv - Initializes new environment variable,
 * or modify an existing one
 * @inf: struct  containing potential arguments.
 *  Return: 0
 */
int my_setenv(info_t *inf)
{
	if (inf->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(inf, inf->argv[1], inf->argv[2]))
		return (0);
	return (1);
}

/**
 * my_unsetenv - removes an environment variable
 * @inf: struct containing potential arguments
 * used to maintain function prototype.
 *
 * Return: 0
 */
int my_unsetenv(info_t *inf)
{
	int k;

	if (inf->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (k = 1; k <= inf->argc; k++)
		_unsetenv(inf, inf->argv[k]);

	return (0);
}

/**
 * populate_env_list - populates env linked list
 * @inf: structure containing potential arguments
 * Return: 0
 */
int populate_env_list(info_t *inf)
{
	list_t *nod = NULL;
	size_t k = 0;

	while (environ[k])
	{
		add_node_end(&nod, environ[k], 0);
		k++;
	}

	inf->env = nod;
	return (0);
}
