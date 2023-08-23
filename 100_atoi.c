#include "mainshell.h"

/**
 * interactive - checks whether the shell is interative
 * @info: struct address
 *
 * Return: 1 if yes, 0 otherwise
 */
int interactive(info_t *info)
{
	return (isatty(STDIN_FILENO) && info->readfd <= 2);
}

/**
 * is_delim - checks whether character is a delimeter
 * @c: the character to check
 * @delim: the delimeter string
 * Return: 1 if yes, 0 otherwise
 */
int is_delim(char c, char *delim)
{
	while (*delim)
		if (*delim++ == c)
			return (1);
	return (0);
}

/**
 * _isalpha - checks for alphabetic character
 * @c: The inputted character
 * Return: 1 if yes, 0 otherwise
 */

int _isalpha(int c)
{
	if ((c >= 'a' && c <= 'z') || (c >= 'A' && c <= 'Z'))
		return (1);
	else
		return (0);
}

/**
 * _atoi - converts a string to an integer
 * @s: the string to be converted
 * Return: 0 if no numbers in string, converted number otherwise
 */

int _atoi(char *s)
{
	int x, x1 = 1, x2 = 0, x3;
	unsigned int ans = 0;

	for (x = 0; s[x] != '\0' && x2 != 2; x++)
	{
		if (s[x] == '-')
			x1 *= -1;

		if (s[x] >= '0' && s[x] <= '9')
		{
			x2 = 1;
			ans *= 10;
			ans += (s[x] - '0');
		}
		else if (x2 == 1)
			x2 = 2;
	}

	if (x1 == -1)
		x3 = -ans;
	else
		x3 = ans;

	return (x3);
}
