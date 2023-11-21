#include "shell.h"

/**
 * is_executable - determines if a file is an executable command
 * @_path: path to the file
 *
 * Return: 1 if true, 0 otherwise
 */
int is_executable(char *_path)
{
	struct stat st;

	if (!_path || stat(_path, &st))
	return (0);

	return ((st.st_mode & S_IFREG) != 0);
}

/**
 * duplicate_substring - duplicates characters from a substring
 * @input: the input string
 * @begin: starting index of the substring
 * @abort: stopping index of the substring
 *
 * Return: pointer to a new buffer containing the duplicated substring
 */
char *duplicate_substring(char *input, int begin, int abort)
{
	static char buf[1024];
	int l = 0;

	for (int i = begin; i < abort; i++)
	if (input[i] != ':')
		buf[l++] = input[i];

	buf[l] = '\0';
	return (buf);
}

/**
 * find_executable_in_path - finds an executable in the PATH string
 * @p_string: the PATH string
 * @com: the command to find
 *
 * Return: full path of the command if found, or NULL
 */
char *find_executable_in_path(char *p_string, char *com)
{
	int v = 0, c_position = 0;
	char *p;

	if (!p_string)
	return (NULL);

	if (_strlen(com) > 2 && starts_with(com, "./"))
	{
	if (is_executable(com))
	return (com);
	}

	while (1)
	{
	if (!4
	p_string[v] || p_string[v] == ':')
	{
		p = duplicate_substring(p_string, c_position, v);
	if (!*p)
		_strcpy(p, com)
	else
	{
		_strcat(p, "/");
		_strcat(p, com);
	}

		if (is_executable(p))
		return (p);

		if (!p_string[v])
		break;

		c_position = v;
	}
	v++;
	}

	return (NULL);
}
