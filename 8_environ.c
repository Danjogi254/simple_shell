#include "mainshell.h"

/**
 * get_environ - returns an array of strings to our environment
 * @info: Structure containing potential arguments.
 * Return: Always 0
 */
char **get_environ(info_t *info)
{
	if (!info->environ || info->env_changed)
	{
		info->environ = list_to_strings(info->env);
		info->env_changed = 0;
	}

	return (info->environ);
}

/**
 * _unsetenv - unset the environment variable
 * @info: Structure containing potential arguments
 * @var: property of a string environment
 * Return: 1 success 0 otherwise
 */
int _unsetenv(info_t *info, char *var)
{
	list_t *node = info->env;
	size_t a = 0;
	char *b;

	if (!node || !var)
		return (0);

	while (node)
	{
		b = starts_with(node->str, var);
		if (b && *b == '=')
		{
			info->env_changed = delete_node_at_index(&(info->env), a);
			a = 0;
			node = info->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (info->env_changed);
}

/**
 * _setenv - Sets a new environment
 * @info: Structure containing potential arguments
 * @var: property of a string environment variable
 * @value: value of the string environment variable
 *  Return: Always 0
 */
int _setenv(info_t *info, char *var, char *value)
{
	char *p = NULL;
	list_t *node;
	char *pp;

	if (!var || !value)
		return (0);

	p = malloc(_strlen(var) + _strlen(value) + 2);
	if (!p)
		return (1);
	_strcpy(p, var);
	_strcat(p, "=");
	_strcat(p, value);
	node = info->env;
	while (node)
	{
		pp = starts_with(node->str, var);
		if (pp && *pp == '=')
		{
			free(node->str);
			node->str = p;
			info->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(info->env), p, 0);
	free(p);
	info->env_changed = 1;
	return (0);
}
