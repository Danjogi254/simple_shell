#include "mainshell.h"

/**
 * _myenv - printing current environment
 * @info: Structure containing potential arguments.
 * Return: Always 0 success
 */
int _myenv(info_t *info)
{
	print_list_str(info->env);
	return (0);
}

/**
 * _getenv - getting environment variable value
 * @info: Structure containing potential arguments
 * @name: environ variable name
 * Return: the variable value
 */
char *_getenv(info_t *info, const char *name)
{
	list_t *node = info->env;
	char *a;

	while (node)
	{
		a = starts_with(node->str, name);
		if (a && *a)
			return (a);
		node = node->next;
	}
	return (NULL);
}

/**
 * _mysetenv - makes a new environment variable or reset an existing
 * @info: Structure containing potential arguments
 *  Return: Always 0
 */
int _mysetenv(info_t *info)
{
	if (info->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(info, info->argv[1], info->argv[2]))
		return (0);
	return (1);
}

/**
 * _myunsetenv - Deletes an environment variable
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
int _myunsetenv(info_t *info)
{
	int b;

	if (info->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (b = 1; b <= info->argc; b++)
		_unsetenv(info, info->argv[b]);

	return (0);
}

/**
 * populate_env_list - populates environment linked list
 * @info: Structure containing potential arguments. Used to maintain
 *          constant function prototype.
 * Return: Always 0
 */
int populate_env_list(info_t *info)
{
	list_t *node = NULL;
	size_t b;

	for (b = 0; environ[b]; b++)
		add_node_end(&node, environ[b], 0);
	info->env = node;
	return (0);
}
