#include "mainshell.h"

/**
 * add_node - adds a node at start
 * @head: address of pointer
 * @str: str
 * @num: node index used by history
 * Return: heads
 */
list_t *add_node(list_t **head, const char *str, int num)
{
	list_t *heads;

	if (!head)
		return (NULL);
	heads = malloc(sizeof(list_t));
	if (!heads)
		return (NULL);
	_memset((void *)heads, 0, sizeof(list_t));
	heads->num = num;
	if (str)
	{
		heads->str = _strdup(str);
		if (!heads->str)
		{
			free(heads);
			return (NULL);
		}
	}
	heads->next = *head;
	*head = heads;
	return (heads);
}

/**
 * add_node_end - adds a node at end
 * @head: address of pointer to head node
 * @str: str
 * @num: node index used by history
 * Return: size of list
 */
list_t *add_node_end(list_t **head, const char *str, int num)
{
	list_t *node1, *node2;

	if (!head)
		return (NULL);

	node2 = *head;
	node1 = malloc(sizeof(list_t));
	if (!node1)
		return (NULL);
	_memset((void *)node1, 0, sizeof(list_t));
	node1->num = num;
	if (str)
	{
		node1->str = _strdup(str);
		if (!node1->str)
		{
			free(node1);
			return (NULL);
		}
	}
	if (node2)
	{
		while (node2->next)
			node2 = node2->next;
		node2->next = node1;
	}
	else
		*head = node1;
	return (node1);
}

/**
 * print_list_str - prints the str element of a linked list
 * @h: pointer to first node
 * Return: a
 */
size_t print_list_str(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->str ? h->str : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 * delete_node_at_index - deletes node
 * @head: address of pointer to first node
 * @index: index of node to delete
 * Return: 1 on success, 0 on otherwise
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node1, *node2;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node1 = *head;
		*head = (*head)->next;
		free(node1->str);
		free(node1);
		return (1);
	}
	node1 = *head;
	while (node1)
	{
		if (a == index)
		{
			node2->next = node1->next;
			free(node1->str);
			free(node1);
			return (1);
		}
		a++;
		node2 = node1;
		node1 = node1->next;
	}
	return (0);
}

/**
 * free_list - frees nodes of a limked list
 * @head_ptr: address of pointer to head node
 * Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node1, *node2, *start;

	if (!head_ptr || !*head_ptr)
		return;
	start = *head_ptr;
	node1 = start;
	while (node1)
	{
		node2 = node1->next;
		free(node1->str);
		free(node1);
		node1 = node2;
	}
	*head_ptr = NULL;
}
