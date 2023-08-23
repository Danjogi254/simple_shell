#include "mainshell.h"

/**
 * _memset - fills memory with a constant byte
 * @s: memory area pointer
 * @b: bytes used to fill
 * @n: the number of bytes to be filled
 * Return: (s)
 */
char *_memset(char *s, char b, unsigned int n)
{
	unsigned int a;

	for (a = 0; a < n; a++)
		s[a] = b;
	return (s);
}

/**
 * ffree - frees a string of strings
 * @pp: string of strings
 */
void ffree(char **pp)
{
	char **x = pp;

	if (!pp)
		return;
	while (*pp)
		free(*pp++);
	free(x);
}

/**
 * _realloc - reallocates a block of memory
 * @ptr: mallocated block pointer
 * @old_size: byte size of previous block
 * @new_size: byte size of new block
 * Return: pointer to da ol'block nameen.
 */
void *_realloc(void *ptr, unsigned int old_size, unsigned int new_size)
{
	char *x;

	if (!ptr)
		return (malloc(new_size));
	if (!new_size)
		return (free(ptr), NULL);
	if (new_size == old_size)
		return (ptr);

	x = malloc(new_size);
	if (!x)
		return (NULL);

	old_size = old_size < new_size ? old_size : new_size;
	while (old_size--)
		x[old_size] = ((char *)ptr)[old_size];
	free(ptr);
	return (x);
}
