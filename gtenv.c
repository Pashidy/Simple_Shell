#include "shell.h"

/**
 * retrieveEnvironment - returns the string array copy of our environ
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **retrieveEnvironment(info_t *info)
{
	if (!info->environ || info->envChanged)
	{
		info->environ = convertListToStrings(info->env);
		info->envChanged = 0;
	}

	return (info->environ);
}

/**
 * removeEnvironmentVariable - Remove an environment variable
 * @info: Structure containing potential arguments.
 * @variable: the string env variable property
 * Return: 1 on delete, 0 otherwise
 */
int removeEnvironmentVariable(info_t *info, char *variable)
{
	list_t *currentNode = info->env;
	size_t index = 0;
	char *position;

	if (!currentNode || !variable)
		return (0);

	while (currentNode)
	{
		position = startsWith(currentNode->str, variable);
		if (position && *position == '=')
		{
			info->envChanged = deleteNodeAtIndex(&(info->env), index);
			index = 0;
			currentNode = info->env;
			continue;
		}
		currentNode = currentNode->next;
		index++;
	}
	return (info->envChanged);
}

/**
 * setEnvironmentVariable - Initialize a new environment variable,
 *             or modify an existing one
 * @info: Structure containing potential arguments.
 * @variable: the string env variable property
 * @value: the string env variable value
 * Return: Always 0
 */
int setEnvironmentVariable(info_t *info, char *variable, char *value)
{
	char *buffer = NULL;
	list_t *currentNode;
	char *position;

	if (!variable || !value)
		return (0);

	buffer = malloc(_strlen(variable) + _strlen(value) + 2);
	if (!buffer)
		return (1);

	_strcpy(buffer, variable);
	_strcat(buffer, "=");
	_strcat(buffer, value);
	currentNode = info->env;

	while (currentNode)
	{
		position = startsWith(currentNode->str, variable);
		if (position && *position == '=')
		{
			free(currentNode->str);
			currentNode->str = buffer;
			info->envChanged = 1;
			return (0);
		}
		currentNode = currentNode->next;
	}

	addNodeEnd(&(info->env), buffer, 0);
	free(buffer);
	info->envChanged = 1;
	return (0);
}

