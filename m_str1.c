#include "shell.h"

/**
 * string_length - returns the length of a string
 * @s: string length to check
 *
 * Return: integer length of string
 */
int string_length(char *s)
{
	int lengt = 0;

	if (!s)
	return (0);

	while (*s++)
	lengt++;

	return (lengt);
}

/**
 * string_compare - performs lexicographic comparison of two strings.
 * @s1: the first string
 * @s2: the second string
 *
 * Return: negative if s1 < s2, positive if s1 > s2, zero if s1 == s2
 */
int string_compare(char *s1, char *s2)
{
	while (*s1 && *s2)
	{
	if (*s1 != *s2)
	return (*s1 - *s2);

	s1++;
	s2++;
	}

	if (*s1 == *s2)
	return (0);
	else
	return (*s1 < *s2 ? -1 : 1);
}

/**
 * string_starts_with - checks if haystack starts with needle
 * @h_stack: string to search
 * @pin: the substring to find
 *
 * Return: address of next char of h_stack or NULL
 */
char *string_starts_with(const char *h_stack, const char *pin)
{
	while (*pin)
	if (*pin++ != *h_stack++)
	return (NULL);

	return ((char *)h_stack);
}

/**
 * string_concatenate - concatenates two strings
 * @dest: the destination buffer
 * @root: the source buffer
 *
 * Return: pointer to destination buffer
 */
char *string_concatenate(char *dest, char *root)
{
	char *result = dest;

	while (*dest)
	dest++;

	while (*root)
	*dest++ = *root++;

	*dest = *root;

	return (result);
}
