#include "shell.h"

/**
 * free_and_null - frees a pointer and NULLs the address
 * @p: address of the pointer to free
 *
 * Return: 1 if freed, otherwise 0.
 */
int free_and_null(void **p)
{
	if (p && *p)
	{
	free(*p);
	*p = NULL;
	return (1);
	}

	return (0);
}
