#include "mainshell.h"

/**
 * input_buf - buffers chained commands
 * @info: parameter struct
 * @buf: address of buffer
 * @len: address of len var
 * Return: len1
 */
ssize_t input_buf(info_t *info, char **buf, size_t *len)
{
	ssize_t len1 = 0;
	size_t len2 = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigintHandler);
#if USE_GETLINE
		len1 = getline(buf, &len2, stdin);
#else
		len1 = _getline(info, buf, &len2);
#endif
		if (len1 > 0)
		{
			if ((*buf)[len1 - 1] == '\n')
			{
				(*buf)[len1 - 1] = '\0';
				len1--;
			}
			info->linecount_flag = 1;
			remove_comments(*buf);
			build_history_list(info, *buf, info->histcount++);
			{
				*len = len1;
				info->cmd_buf = buf;
			}
		}
	}
	return (len1);
}

/**
 * get_input - finds a line
 * @info: parameter struct
 * Return: c
 */
ssize_t get_input(info_t *info)
{
	static char *buf1;
	static size_t a, b, len;
	ssize_t c = 0;
	char **buf2 = &(info->arg), *p;

	_putchar(BUF_FLUSH);
	c = input_buf(info, &buf1, &len);
	if (c == -1)
		return (-1);
	if (len)
	{
		b = a;
		p = buf1 + a;

		check_chain(info, buf1, &b, a, len);
		while (b < len)
		{
			if (is_chain(info, buf1, &b))
				break;
			b++;
		}

		a = b + 1;
		if (a >= len)
		{
			a = len = 0;
			info->cmd_buf_type = CMD_NORM;
		}

		*buf2 = p;
		return (_strlen(p));
	}

	*buf2 = buf1;
	return (c);
}

/**
 * read_buf - used to reada buffer
 * @info: parameter struct
 * @buf: buffer
 * @i: size
 * Return: c
 */
ssize_t read_buf(info_t *info, char *buf, size_t *i)
{
	ssize_t c = 0;

	if (*i)
		return (0);
	c = read(info->readfd, buf, READ_BUF_SIZE);
	if (c >= 0)
		*i = c;
	return (c);
}

/**
 * _getline - gets the next line of input from STDIN
 * @info: parameter struct
 * @ptr: address of pointer to buffer, preallocated or NULL
 * @length: size of preallocated ptr buffer if not NULL
 *
 * Return: bb
 */
int _getline(info_t *info, char **ptr, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t len1, len2;
	size_t a;
	ssize_t b = 0, bb = 0;
	char *p1 = NULL, *p2 = NULL, *c;

	p1 = *ptr;
	if (p1 && length)
		bb = *length;
	if (len1 == len2)
		len1 = len2 = 0;

	b = read_buf(info, buf, &len2);
	if (b == -1 || (b == 0 && len2 == 0))
		return (-1);

	c = _strchr(buf + len1, '\n');
	a = c ? 1 + (unsigned int)(c - buf) : len2;
	p2 = _realloc(p1, bb, bb ? bb + a : a + 1);
	if (!p2)
		return (p1 ? free(p1), -1 : -1);

	if (bb)
		_strncat(p2, buf + len1, a - len1);
	else
		_strncpy(p2, buf + len1, a - len1 + 1);

	bb += a - len1;
	len1 = a;
	p1 = p2;

	if (length)
		*length = bb;
	*ptr = p1;
	return (bb);
}

/**
 * sigintHandler - blocks ctrl-C
 * @sig_num: the signal number
 *
 * Return: void
 */
void sigintHandler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
