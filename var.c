#include "shell.h"

/**
 * is_chain_delimiter - tests if the current char
 * in buffer is a chain delimiter
 *
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 *
 * Return: 1 if chain delimiter, 0 otherwise
 */
int is_chain_delimiter(info_t *info, char *buf, size_t *p)
{
	size_t e = *p;

	if (buf[e] == '|' && buf[e + 1] == '|')
	{
		buf[e] = 0;
		e++;
		info->cmd_buf_type = CMD_OR;
	}
	else if (buf[e] == '&' && buf[e + 1] == '&')
	{
		buf[e] = 0;
		e++;
		info->cmd_buf_type = CMD_AND;
	}
	else if (buf[e] == ';') /* found end of this command */
	{
		buf[e] = 0; /* replace semicolon with null */
		info->cmd_buf_type = CMD_CHAIN;
	}
	else
		return (0);

	*p = e;
	return (1);
}

/**
 * check_chain - checks if we should continue chaining based on the last status
 * @info: the parameter struct
 * @buf: the char buffer
 * @p: address of the current position in buf
 * @i: starting position in buf
 * @len: length of buf
 *
 * Return: Void
 */
void check_chain(info_t *info, char *buf, size_t *p, size_t i, size_t len)
{
	size_t e = *p;

	if (info->cmd_buf_type == CMD_AND && info->status)
	{
		buf[i] = 0;
		e = len;
	}
	else if (info->cmd_buf_type == CMD_OR && !info->status)
	{
		buf[i] = 0;
		e = len;
	}

	*p = e;
}

/**
 * replace_alias - replaces aliases in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_alias(info_t *info)
{
	int e;
	list_t *node;
	char *q;

	for (e = 0; e < 10; e++)
	{
		node = node_starts_with(info->alias, info->argv[0], '=');
		if (!node)
			return (0);

		free(info->argv[0]);
		q = _strchr(node->str, '=');

		if (!q)
			return (0);

		q = _strdup(q + 1);

		if (!q)
			return (0);

		info->argv[0] = q;
	}
	return (1);
}

/**
 * replace_vars - replaces variables in the tokenized string
 * @info: the parameter struct
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_vars(info_t *info)
{
	int i = 0;
	list_t *node;

	for (i = 0; info->argv[i]; i++)
	{
		if (info->argv[i][0] != '$' || !info->argv[i][1])
			continue;

		if (!_strcmp(info->argv[i], "$?"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(info->status, 10, 0)));
		}
		else if (!_strcmp(info->argv[i], "$$"))
		{
			replace_string(&(info->argv[i]),
						   _strdup(convert_number(getpid(), 10, 0)));
		}
		else
		{
			node = node_starts_with(info->env, &info->argv[i][1], '=');
			if (node)
				replace_string(&(info->argv[i]), _strdup(_strchr(node->str, '=') + 1));
			else
				replace_string(&info->argv[i], _strdup(""));
		}
	}
	return (1);
}

/**
 * replace_string - replaces a string
 * @old: address of the old string
 * @new: new string
 *
 * Return: 1 if replaced, 0 otherwise
 */
int replace_string(char **old, char *new)
{
	free(*old);
	*old = new;
	return (1);
}
