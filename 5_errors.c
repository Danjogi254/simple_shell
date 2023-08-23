#include "mainshell.h"

/**
 * _erratoi - a convertor of a string to am int
 * @s: the string
 * Return: 0 if no numbers in string, converted number otherwise
 *       -1 on error
 */
int _erratoi(char *s)
{
	int a = 0;
	unsigned long int answer = 0;

	if (*s == '+')
		s++;  /* TODO: why does this make main return 255? */
	for (a = 0;  s[a] != '\0'; a++)
	{
		if (s[a] >= '0' && s[a] <= '9')
		{
			answer *= 10;
			answer += (s[a] - '0');
			if (answer > INT_MAX)
				return (-1);
		}
		else
			return (-1);
	}
	return (answer);
}

/**
 * print_error - gives an error message
 * @info: the parameter & return struct
 * @estr: string containing a specific error type
 * Return: 0 if no numbers in string, converted number otherwise
 *        -1 on error
 */
void print_error(info_t *info, char *estr)
{
	_eputs(info->fname);
	_eputs(": ");
	print_d(info->line_count, STDERR_FILENO);
	_eputs(": ");
	_eputs(info->argv[0]);
	_eputs(": ");
	_eputs(estr);
}

/**
 * print_d - prints a decimal number (base 10)
 * @input: the input
 * @fd: the filedescriptor
 * Return: number of characters printed
 */
int print_d(int input, int fd)
{
	int (*__putchar)(char) = _putchar;
	int a, ct = 0;
	unsigned int b, cur;

	if (fd == STDERR_FILENO)
		__putchar = _eputchar;
	if (input < 0)
	{
		b = -input;
		__putchar('-');
		ct++;
	}
	else
		b = input;
	cur = b;
	for (a = 1000000000; a > 1; a /= 10)
	{
		if (b / a)
		{
			__putchar('0' + cur / a);
			ct++;
		}
		cur %= a;
	}
	__putchar('0' + cur);
	ct++;

	return (ct);
}

/**
 * convert_number - converter function
 * @num: number
 * @base: base
 * @flags: argument flags
 * Return: string
 */
char *convert_number(long int num, int base, int flags)
{
	static char *arr;
	static char buffer[50];
	char s = 0;
	char *pr;
	unsigned long no = num;

	if (!(flags & CONVERT_UNSIGNED) && num < 0)
	{
		no = -num;
		s = '-';

	}
	arr = flags & CONVERT_LOWERCASE ? "0123456789abcdef" : "0123456789ABCDEF";
	pr = &buffer[49];
	*pr = '\0';

	do	{
		*--pr = arr[no % base];
		no /= base;
	} while (no != 0);

	if (s)
		*--pr = s;
	return (pr);
}

/**
 * remove_comments - function replaces first instance of '#' with '\0'
 * @buf: address of the string to modify
 *
 * Return: Always 0;
 */
void remove_comments(char *buf)
{
	int a;

	for (a = 0; buf[a] != '\0'; a++)
		if (buf[a] == '#' && (!a || buf[a - 1] == ' '))
		{
			buf[a] = '\0';
			break;
		}
}
