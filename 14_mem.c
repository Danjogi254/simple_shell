#include "mainshell.h"

/**
 * bfree - frees a pointer
 * @ptr: address of the pointer to free
 *
 * Return: 1 success, otherwise 0.
 */
int bfree(void **ptr)
{
	if (ptr && *ptr)
	{
		free(*ptr);
		*ptr = NULL;
		return (1);
	}
	return (0);
}
