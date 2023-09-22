#include "shell.h"

/*creating environmental variables*/
/*setting the env vars*/
/*unsetiing the env vars*/

/**
 *_my_env - prints out the current environment
 *@infor: pointr to structure info_t
 *Return: 0 on success
 *
 */
int _my_env(info_t *infor)
{
	print_list_str(infor->env);
	return (0);
}


/**
 *_getenv - gets and prints out environmental variables
 *@infor: pointer to structure info_t
 *@name: constant character pinter to string
 *Return: name
 */
char *_getenv(info_t *infor, const char *name)
{
	list_t *node = infor->env;
	char *p;

	while (node)
	{
		p = starts_with(node->ptr, name);
		if (p && *p)
			return (p);
		node = node->next;
	}
	return (NULL);
}

/**
 *_my_setenv - Creating function like _setenv that set environmental vars
 *@infor: pointer to structure info_t
 *Return: 0 always on success
 */
int _my_setenv(info_t *infor)
{
	if (infor->argc != 3)
	{
		_eputs("Incorrect number of arguements\n");
		return (1);
	}
	if (_setenv(infor, infor->argv[1], infor->argv[2]))
		return (0);
	return (1);
}


/**
 *_my_unsetenv - Creating a function that unset set environmental vars
 *@infor: pointer to structure info_t
 *Return: 0
 */
int _my_unsetenv(info_t *infor)
{
	int a;

	if (infor->argc == 1)
	{
		_eputs("Too few arguements.\n");
		return (1);
	}
	for (a = 1; a <= infor->argc; a++)
		_unsetenv(infor, infor->argv[a]);

	return (0);
}

/**
 *populate_env_list - poupulates the environmental linked list
 *@infor: pointer to structure info_t
 *Return: 0 on success
 */
int populate_env_list(info_t *infor)
{
	list_t *node = NULL;
	size_t a;

	for (a = 0; environ[a]; a++)
		add_node_end(&node, environ[a], 0);
	infor->env = node;
	return (0);
}

