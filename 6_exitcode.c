#include "mainshell.h"

/**
 **_strncpy - copies a string
 *@dest: the destination where to be copied
 *@src: the source string
 *@n: the amount of characters to be copied
 *Return: str
 */
char *_strncpy(char *dest, char *src, int n)
{
	int a, b;
	char *str = dest;

	a = 0;
	while (src[a] != '\0' && a < n - 1)
	{
		dest[a] = src[a];
		a++;
	}
	if (a < n)
	{
		b = a;
		while (b < n)
		{
			dest[b] = '\0';
			b++;
		}
	}
	return (str);
}

/**
 **_strncat - concatenates two strings
 *@dest: the first string
 *@src: the second string
 *@n: the amount of bytes to be maximally used
 *Return: str
 */
char *_strncat(char *dest, char *src, int n)
{
	int a, b;
	char *str = dest;

	a = 0;
	b = 0;
	while (dest[a] != '\0')
		a++;
	while (src[b] != '\0' && b < n)
	{
		dest[a] = src[b];
		a++;
		b++;
	}
	if (b < n)
		dest[a] = '\0';
	return (str);
}

/**
 **_strchr - locates a character in a string
 *@s: the string to be searched
 *@c: the character being looked for
 *Return: (s) a pointer to the memory area s
 */
char *_strchr(char *s, char c)
{
	do {
		if (*s == c)
			return (s);
	} while (*s++ != '\0');

	return (NULL);
}
