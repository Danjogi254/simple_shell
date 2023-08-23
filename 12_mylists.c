#include "mainshell.h"

/**
 * list_len - determines length of linked list
 * @h: pointer to first node
 * Return: a
 */
size_t list_len(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * list_to_strings - returns a strings array of a list
 * @head: pointer to first node
 * Return: array of strings
 */
char **list_to_strings(list_t *head)
{
	list_t *nd = head;
	size_t a = list_len(head), b;
	char **strings;
	char *string;

	if (!head || !a)
		return (NULL);
	strings = malloc(sizeof(char *) * (a + 1));
	if (!strings)
		return (NULL);
	for (a = 0; nd; nd = nd->next, a++)
	{
		string = malloc(_strlen(nd->str) + 1);
		if (!string)
		{
			for (b = 0; b < a; b++)
				free(strings[b]);
			free(strings);
			return (NULL);
		}

		string = _strcpy(string, nd->str);
		strings[a] = string;
	}
	strings[a] = NULL;
	return (strings);
}

/**
 * print_list - prints all elements of a linked list
 * @h: pointer to first node*
 * Return: size of list
 */
size_t print_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * node_starts_with - returns node whose string starts with prefix
 * @node: pointer to list head
 * @prefix: string to match
 * @c: the next character after prefix to match
 * Return: NULL
 */
list_t *node_starts_with(list_t *node, char *prefix, char c)
{
	char *st = NULL;

	while (node)
	{
		st = starts_with(node->str, prefix);
		if (st && ((c == -1) || (*st == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}

/**
 * get_node_index - gets the node's index
 * @head: pointer to list head
 * @node: pointer to the node
 * Return: -1
 */
ssize_t get_node_index(list_t *head, list_t *node)
{
	size_t a = 0;

	while (head)
	{
		if (head == node)
			return (a);
		head = head->next;
		a++;
	}
	return (-1);
}
