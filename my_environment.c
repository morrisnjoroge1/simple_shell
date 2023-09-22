#include "shell.h"

/**
 *get_environ - Gets the copy of local environ
 *@infor: pointer to the structure info_t
 *Return: 0 on success
 */
char **get_environ(info_t *infor)
{
	if (!infor->environ || infor->env_changed)
	{
		infor->environ = list_to_string(infor->env);
		infor->env_changed = 0;
	}

	return (infor->environ);
}


/**
 *_setenv - sets environmental variables
 *@infor: pointer to structure
 *@var: pointer to character of variable
 *@value: pointer to character stores var value
 *Return: 0
 */
int _setenv(info_t *infor, char *var, char *value)
{
	char *buf = NULL;
	list_t *node;
	char *pp;

	if (!var || !value)
		return (0);

	buf = malloc(_strlen(var) + _strlen(value) + 2);
	if (!buf)
		return (1);
	_strcpy(buf, var);
	_strcat(buf, "=");
	_strcat(buf, value);
	node = infor->env;
	while (node)
	{
		pp = start_with(node->ptr, var);
		if (pp && *pp == '=')
		{
			free(node->ptr);
			node->ptr = buf;
			infor->env_changed = 1;
			return (0);
		}
		node = node->next;
	}
	add_node_end(&(infor->env), buf, 0);
	free(buf);
	infor->env_changed = 1;
	return (0);
}


/**
 *_unsetenv - Unsets or removes environment variables
 *@infor: pointer to structure
 *@var: pointer to character of variables
 *Return: 0
 */
int _unsetenv(info_t *infor, char *var)
{
	list_t *node = infor->env;
	size_t a = 0;
	char *pp;

	if (!node || !var)
		return (0);

	while (node)
	{
		pp = start_with(node->ptr, var);
		if (pp && *pp == '=')
		{
			infor->env_changed = delete_node_at_index(&(infor->env), a);
			a = 0;
			node = infor->env;
			continue;
		}
		node = node->next;
		a++;
	}
	return (infor->env_changed);
}
