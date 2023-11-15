#include "shell.h"

/**
 * display_history - Displays the history list,
 *
 * @history: Pointer to the history list.
 */
void display_history(list_t *history)
{
	print_list(history);
}

/**
 * my_history - Wrapper function for displaying shell history.
 * @info: Structure containing potential arguments
 * for constant function prototype.
 *
 * Return: 0.
 */
int my_history(info_t *info)
{
	display_history(info->history);
	return (0);
}

/**
 * remove_alias - Removes an alias from the alias list.
 * @info: The parameter structure.
 * @str: String alias.
 *
 * Return: 0 on success, 1 on error.
 */
int remove_alias(info_t *info, char *str)
{
	char *equal_sign = _strchr(str, '=');

	if (!equal_sign)
	return (1);

	*equal_sign = '\0';

	int ret = 1;
	list_t *current = info->alias;
	list_t *prev = NULL;

	while (current)
	{
	if (_strcmp(current->str, str) == 0)
	{
	if (prev)
		prev->next = current->next;
	else
		info->alias = current->next;

		free(current->str);
		free(current);
		ret = 0;
	break;
	}

		prev = current;
		current = current->next;
	}
		*equal_sign = '=';

	return (ret);
}

/**
 * add_alias - Adds or updates an alias in the alias list.
 * @info: The parameter structure.
 * @str: String alias.
 *
 * Return: 0 on success, 1 on error.
 */
int add_alias(info_t *info, char *str)
{
	char *equal_sign = _strchr(str, '=');

	if (!equal_sign)
	return (1);

	if (!*++equal_sign)
	return (remove_alias(info, str));

	remove_alias(info, str);
	list_t *new_node = create_node(str, 0);

	if (!new_node)
	return (1);

	if (add_node_end(&(info->alias), new_node) == NULL)
	return (1);

	return (0);
}

/**
 * display_alias - Displays an alias string.
 * @node: Alias node.
 *
 * Return: 0 on success, 1 on error.
 */
int display_alias(list_t *node)
{
	if (!node)
	return (1);

	char *separator = find_separator(node->str, '=');

	if (!separator)
		return (1);

	char *aliasStart = node->str;

	while (aliasStart <= separator)
	{
		output_character(*aliasStart);
		aliasStart++;
	}

	output_character('\'');
	output_string(separator + 1);
	output_string("'\n");

	return (0);
}

/**
 * find_separator - Finds the separator in an alias string.
 * @alias: Alias string.
 * @separator: Pointer to the separator.
 *
 * Return: Pointer to the separator.
 */
char *find_separator(char *alias, char separator)
{
	while (*alias && *alias != separator)
	alias++;

	return (*alias == separator ? alias : NULL;);
}

/**
 * output_character - Outputs a character.
 * @c: Character to output.
 */
void outputCharacter(char c)
{
	_putchar(c);
}

/**
 * output_string - Outputs a string.
 * @str: String to output.
 */
void output_string(char *str)
{
	_puts(str);
}

/**
 * display_aliases - Displays all aliases in the list.
 * @alias_list: Alias list.
 */
void display_aliases(list_t *alias_list)
{
	list_t *current_alias = alias_list;

	while (current_alias)
	{
		display_alias(current_alias);
		current_alias = current_alias->next;
	}
}

/**
 * _myalias - imitates alias builtin (man alias).
 * @info: Structure containing arguments.
 *
 * Return: Always 0.
 */
int _myalias(info_t *info)
{
	int index = 1;
	char *equal_sign = NULL;
	list_t *alias_node = NULL;

	if (info->argc == 1)
	{
		display_all_aliases(info->alias);
		return (0);
	}
	while (info->argv[index])
	{
		equal_sign = _strchr(info->argv[index], '=');
	if (equal_sign)
		set_alias(info, info->argv[index]);
	else
	{
		alias_node = node_starts_with(info->alias, info->argv[index], '=');
	if (alias_node)
		display_alias(alias_node);
	}

		index++;
	}

	return (0);
}
