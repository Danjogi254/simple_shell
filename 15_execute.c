#include "mainshell.h"

/**
 * is_cmd - checks whether the file is an executable command
 * @info: the info struct
 * @path: path to the file
 * Return: 1 if true, 0 false
 */
int is_cmd(info_t *info, char *path)
{
	struct stat st;

	(void)info;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}

/**
 * dup_chars - duplicates chars
 * @pathstr: the PATH string
 * @start: starting index
 * @stop: stopping index
 * Return: buffer
 */
char *dup_chars(char *pathstr, int start, int stop)
{
	static char buffer[1024];
	int a = 0, b = 0;

	for (b = 0, a = start; a < stop; a++)
		if (pathstr[a] != ':')
			buffer[b++] = pathstr[a];
	buffer[b] = 0;
	return (buffer);
}

/**
 * find_path - finds a cmd path
 * @info: the info struct
 * @pathstr: the PATH string
 * @cmd: the cmd to find
 * Return: full path of cmd if found or NULL
 */
char *find_path(info_t *info, char *pathstr, char *cmd)
{
	int a = 0, pos = 0;
	char *p;

	if (!pathstr)
		return (NULL);
	if ((_strlen(cmd) > 2) && starts_with(cmd, "./"))
	{
		if (is_cmd(info, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstr[a] || pathstr[a] == ':')
		{
			p = dup_chars(pathstr, pos, a);
			if (!*p)
				_strcat(p, cmd);
			else
			{
				_strcat(p, "/");
				_strcat(p, cmd);
			}
			if (is_cmd(info, p))
				return (p);
			if (!pathstr[a])
				break;
			pos = a;
		}
		a++;
	}
	return (NULL);
}
