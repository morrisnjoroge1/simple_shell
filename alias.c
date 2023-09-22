#include "shell.h"

/**
 *set_alias - Function that prints aliases of linked list
 *@infor: pointer to structure info_t
 *@ptr: pointer to character string
 *Return: 0 on success or -1 otherwise
 */
int set_alias(info_t *infor, char *ptr)
{
	char *p;

	p = _strchr(ptr, '=');
	if (!p)
		return (1);
	if (!*++p)
		return (unset_alias(infor, ptr));

	unset_alias(infor, ptr);
	return (add_node_end(&(infor->alias), ptr, 0) == NULL);
}

/**
 *unset_alias - unsets specidied or current alias
 *@infor: pointer to stucture info_t
 *@ptr: pointer to character string
 *Return: 0 on success
 */
int unset_alias(info_t *infor, char *ptr)
{
	char *p, c;
	int ret;

	p = _strchr(ptr, '=');
	if (!p)
		return (1);
	c = *p;
	*p = 0;
	ret = delete_node_at_index(&(infor->alias),
		get_node_index(infor->alias, node_start_with(infor->alias, ptr, -1)));
	*p = c;
	return (ret);
}

/**
 *prints_alias - Function that prints aliases
 *@node: pointer to list_t that has linked lists
 *Return: 0 on success
 */
int prints_alias(list_t *node)
{
	char *p = NULL, *a = NULL;

	if (node)
	{
		p = _strchr(node->ptr, '=');
		for (a = node->ptr; a <= p; a++)
		_putchar(*a);
		_putchar('\'');
		_puts(p + 1);
		_puts("'\n");
		return (0);
	}
	return (1);
}
