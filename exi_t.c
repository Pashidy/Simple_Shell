#include "shell.h"

/**
 * copyString - copies a string
 * @destination: the destination string to be copied to
 * @source: the source string
 * @length: the amount of characters to be copied
 * Return: the concatenated string
 */
char *copyString(char *destination, char *source, int length)
{
	int i, j;
	char *result = destination;

	i = 0;
	while (source[i] != '\0' && i < length - 1)
	{
		destination[i] = source[i];
		i++;
	}
	if (i < length)
	{
		j = i;
		while (j < length)
		{
			destination[j] = '\0';
			j++;
		}
	}
	return (result);
}

/**
 * concatenateString - concatenates two strings
 * @first: the first string
 * @second: the second string
 * @maxLength: the amount of bytes to be maximally used
 * Return: the concatenated string
 */
char *concatenateString(char *first, char *second, int maxLength)
{
	int i, j;
	char *result = first;

	i = 0;
	j = 0;
	while (first[i] != '\0')
		i++;
	while (second[j] != '\0' && j < maxLength)
	{
		first[i] = second[j];
		i++;
		j++;
	}
	if (j < maxLength)
		first[i] = '\0';
	return (result);
}

/**
 * findCharacter - locates a character in a string
 * @str: the string to be parsed
 * @target: the character to look for
 * Return: a pointer to the memory area of str
 */
char *findCharacter(char *str, char target)
{
	do {
		if (*str == target)
			return (str);
	} while (*str++ != '\0');

	return (NULL);
}
