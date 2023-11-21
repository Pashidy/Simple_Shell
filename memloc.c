#include "shell.h"

/**
 * fill_memory - fills memory with a constant byte
 * @mem: pointer to the memory area
 * @byt: the byte to fill *memory with
 * @vol: the amount of bytes to be filled
 *
 * Return: a pointer to the memory area
 */
char *fill_memory(char *mem, char byt, unsigned int vol)
{
	for (unsigned int q = 0; q < vol; q++)
	mem[q] = byt;
	return (mem);
}

/**
 * free_string_array - frees a string array
 * @s_array: string array to free
 */
void free_string_array(char **s_array)
{
	char **t = s_array;

	if (!s_array)
	return;

	while (*s_array)
	free(*s_array++);

	free(t);
}

/**
 * reallocate_memory - reallocates a block of memory
 * @p: pointer to previous malloc'ated block
 * @o_size: byte size of the previous block
 * @n_size: byte size of the new block
 *
 * Return: pointer to the reallocated block
 */
void *reallocate_memory(void *p, unsigned int o_size, unsigned int n_size)
{
	char *n_ptr;

	if (!p)
	return (malloc(n_size));

	if (!n_size)
	return (free(p), NULL);

	if (n_size == o_size)
	return (p);

	n_ptr = malloc(n_size);

	if (!n_ptr)
	return (NULL);

	o_size = o_size < n_size ? o_size : n_size;

	while (o_size--)
	n_ptr[o_size] = ((char *)p)[o_size];

	free(p);
	return (n_ptr);
}
