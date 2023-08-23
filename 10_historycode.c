#include "mainshell.h"

/**
 * get_history_file - file history finder
 * @info: parameter struct
 * Return: Buffer
 */

char *get_history_file(info_t *info)
{
	char *buffer, *directory;

	directory = _getenv(info, "HOME=");
	if (!directory)
		return (NULL);
	buffer = malloc(sizeof(char) * (_strlen(directory) + _strlen(HIST_FILE) + 2));
	if (!buffer)
		return (NULL);
	buffer[0] = 0;
	_strcpy(buffer, directory);
	_strcat(buffer, "/");
	_strcat(buffer, HIST_FILE);
	return (buffer);
}

/**
 * write_history - creates a new file or make changes to an existing
 * @info: the parameter struct
 * Return: 1 on success, else -1
 */
int write_history(info_t *info)
{
	ssize_t file;
	char *name = get_history_file(info);
	list_t *node = NULL;

	if (!name)
		return (-1);

	file = open(name, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(name);
	if (file == -1)
		return (-1);
	for (node = info->history; node; node = node->next)
	{
		_putsfd(node->str, file);
		_putfd('\n', file);
	}
	_putfd(BUF_FLUSH, file);
	close(file);
	return (1);
}

/**
 * read_history - reads file history
 * @info: the parameter struct
 * Return: histcount on success, 0 otherwise
 */
int read_history(info_t *info)
{
	int a, end = 0, counter = 0;
	ssize_t file, rdlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *name = get_history_file(info);

	if (!name)
		return (0);

	file = open(name, O_RDONLY);
	free(name);
	if (file == -1)
		return (0);
	if (!fstat(file, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rdlen = read(file, buf, fsize);
	buf[fsize] = 0;
	if (rdlen <= 0)
		return (free(buf), 0);
	close(file);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(info, buf + end, counter++);
			end = a + 1;
		}
	if (end != a)
		build_history_list(info, buf + end, counter++);
	free(buf);
	info->histcount = counter;
	while (info->histcount-- >= HIST_MAX)
		delete_node_at_index(&(info->history), 0);
	renumber_history(info);
	return (info->histcount);
}

/**
 * build_history_list - adds entry to a history linked list
 * @info: Structure containing potential arguments.
 * @buf: buffer
 * @linecount: the history linecount
 * Return: Always 0
 */
int build_history_list(info_t *info, char *buf, int linecount)
{
	list_t *node = NULL;

	if (info->history)
		node = info->history;
	add_node_end(&node, buf, linecount);

	if (!info->history)
		info->history = node;
	return (0);
}

/**
 * renumber_history - renumbeing history linked list after editing
 * @info: Structure containing potential arguments
 * Return: the new histcount
 */
int renumber_history(info_t *info)
{
	list_t *node = info->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (info->histcount = a);
}
