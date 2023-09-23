#include "shell.h"

/**
 *list_len - returns the length of list
 *@h: pointer to the first node
 *Return: size of list
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
 *list_to_string - Function that returns array of list
 *@head: points to first node
 *Return: array of stirngs list
 */
char **list_to_string(list_t *head)
{
	list_t *node = head;
	size_t a = list_len(head), b;
	char **stars;
	char *ptr;

	if (!head || !a)
		return (NULL);
	stars = malloc(sizeof(char *) * (a + 1));
	if (!stars)
		return (NULL);
	for (a = 0; node; node = node->next, a++)
	{
		ptr = malloc(_strlen(node->ptr) + 1);
		if (!ptr)
		{
			for (b = 0; b < a; b++)
				free(stars[b]);
			free(stars);
			return (NULL);
		}

		ptr = _strcpy(ptr, node->ptr);
		stars[a] = ptr;
	}
	stars[a] = NULL;
	return (stars);
}


/**
 *prints_list - prints all the elements in list
 *@h: points to he first node
 *Return: size of list
 */
size_t prints_list(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(convert_number(h->num, 10, 0));
		_putchar(':');
		_putchar(' ');
		_puts(h->ptr ? h->ptr : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 *node_start_with - checks node that start with specific character
 *@node: points to head node in list
 *@prefix: specified string tob be searched or matched
 *@c: checked character
 *Return: next node after matched node
 */
list_t *node_start_with(list_t *node, char *prefix, char c)
{
	char *pp = NULL;

	while (node)
	{
		pp = start_with(node->ptr, prefix);
		if (pp && ((c == -1) || (*pp == c)))
			return (node);
		node = node->next;
	}
	return (NULL);
}


/**
 *get_node_index - gets node at specified index
 *@head: points to head node
 *@node: points to node
 *Return: -1 or index of node
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
