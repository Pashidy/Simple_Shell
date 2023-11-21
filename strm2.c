#include "shell.h"

/**
 * copy_string - copies a string
 * @destin: the destination
 * @root: the source
 *
 * Return: pointer to destination
 */
char *copy_string(char *destin, char *root)
{
	int p = 0;

	if (destin == root || root == NULL)
	return (destin);

	while (root[p])
	{
	destin[p] = root[p];
		p++;
	}

	destin[p] = '\0';
	return (destin);
}

/**
 * duplicate_string - duplicates a string
 * @s: the string to duplicate
 *
 * Return: pointer to the duplicated string
 */
char *duplicate_string(const char *s)
{
	int length = 0;
	char *result;

	if (s == NULL)
	return (NULL);

	while (*s++)
	length++;

	result = malloc(sizeof(char) * (length + 1));

	if (!result)
	return (NULL);

	for (length++; length--;)
		result[length] = *--s;

	return (result);
}

/**
 * print_string - prints an input string
 * @s: the string to be printed
 *
 * Return: Nothing
 */
void print_string(char *s)
{
	int point = 0;

	if (!s)
	return;

	while (s[point] != '\0')
	{
	output_character(s[point]);
	point++;
	}
}

/**
 * output_character - writes the character to stdout
 * @def: The character to print
 *
 * Return: On success 1.
 * On error, -1 is returned, and errno is set appropriately.
 */
int output_character(char def)
{
	static int pointr;
	static char buffer[WRITE_BUFFER_SIZE];

	if (def == BUFFER_FLUSH || pointr >= WRITE_BUFFER_SIZE)
	{
	write(1, buffer, pointr);
	pointr = 0;
	}

	if (def != BUFFER_FLUSH)
		buffer[pointr++] = def;

	return (1);
}

