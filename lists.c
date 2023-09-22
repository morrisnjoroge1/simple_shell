#include "shell.h"

/**
 *add_node - Function that add node at the begining of linked list
 *@head: pointer to the first node of the list
 *@ptr: pointer to character string points to field of list
 *@num: integer
 *Return: new address of new node
 */
list_t *add_node(list_t **head, const char *ptr, int num)
{
	list_t *add_head;

	if (!head)
		return (NULL);
	add_head = malloc(sizeof(list_t));
	if (!add_head)
		return (NULL);
	_memset((void *)add_head, 0, sizeof(list_t));
	add_head->num = num;
	if (ptr)
	{
		add_head->ptr = _strdup(ptr);
		if (!add_head->ptr)
		{
			free(add_head);
			return (NULL);
		}
	}
	add_head->next = *head;
	*head = add_head;
	return (add_head);
}



/**
 *add_node_end - Adds new node at the end of linked list
 *@head: double pointer to the first node of the list
 *@ptr: pointer to character string field of list
 *@num: integer
 *Return: address of new node
 */
list_t *add_node_end(list_t **head, const char *ptr, int num)
{
	list_t *add_node, *node;

	if (!head)
		return (NULL);

	node = *head;
	add_node = malloc(sizeof(list_t));
	if (!add_node)
		return (NULL);
	_memset((void *)add_node, 0, sizeof(list_t));
	add_node->num = num;
	if (ptr)
	{
		add_node->ptr = _strdup(ptr);
		if (!add_node->ptr)
		{
			free(add_node);
			return (NULL);
		}
	}
	if (node)
	{
		while (node->next)
			node = node->next;
		node->next = add_node;
	}
	else
		*head = add_node;
	return (add_node);
}


/**
 *delete_node_at_index - Deletes node in list at specified index
 *@head: double pointer to first node in the list
 *@index: index of node
 *Return: 1 upon success or 0 otherwise
 */
int delete_node_at_index(list_t **head, unsigned int index)
{
	list_t *node, *prev_node;
	unsigned int a = 0;

	if (!head || !*head)
		return (0);

	if (!index)
	{
		node = *head;
		*head = (*head)->next;
		free(node->ptr);
		free(node);
		return (1);
	}
	node = *head;
	while (node)
	{
		if (a == index)
		{
			prev_node->next = node->next;
			free(node->ptr);
			free(node);
			return (1);
		}
		a++;
		prev_node = node;
		node = node->next;
	}
	return (0);
}


/**
 *print_list_ptr - prints the nodes in linked list string
 *@h: points to the first node in list
 *Return: the size of list
 */
size_t print_list_ptr(const list_t *h)
{
	size_t a = 0;

	while (h)
	{
		_puts(h->ptr ? h->ptr : "(nil)");
		_puts("\n");
		h = h->next;
		a++;
	}
	return (a);
}

/**
 *free_list - fress list in the linked list
 *@head_ptr: double pointer to first node header
 *Return: void
 */
void free_list(list_t **head_ptr)
{
	list_t *node, *next_node, *head;

	if (!head_ptr || !*head_ptr)
		return;
	head = *head_ptr;
	node = head;
	while (node)
	{
		next_node = node->next;
		free(node->ptr);
		free(node);
		node = next_node;
	}
	*head_ptr = NULL;
}
