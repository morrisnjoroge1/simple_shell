#include "shell.h"








/**
 *is_chain - checks for chain delimeter in buffer
 *@infor: pointer to structure
 *@buf: buffer
 *@pp: address of current buffer
 *Return: 1 if true or 0
 */
int is_chain(info_t *infor, char *buf, size_t *pp)
{
	size_t b = *pp;

	if (buf[b] == '|' && buf[b + 1] == '|')
	{
		buf[b] = 0;
		b++;
		infor->cmd_buf_command = CMD_OR;
	}
	else if (buf[b] == '&' && buf[b + 1] == '&')
	{
		buf[b] = 0;
		b++;
		infor->cmd_buf_command = CMD_AND;
	}
	else if (buf[b] == ';')
	{
		buf[b] = 0;
		infor->cmd_buf_command = CMD_CHAIN;
	}
	else
		return (0);
	*pp = b;
	return (1);
}



/**
 *check_chain - checks if there is to continue with the chaining
 *@infor: pointer to structure
 *@buf: character buffer
 *@pp: integer
 *@a: integer
 *@len: integer representing length
 *Return: void
 */
void check_chain(info_t *infor, char *buf, size_t *pp, size_t a, size_t len)
{
	size_t b = *pp;

	if (infor->cmd_buf_command == CMD_AND)
	{
		if (infor->status)
		{
			buf[a] = 0;
			b = len;
		}
	}
	if (infor->cmd_buf_command == CMD_OR)
	{
		if (!infor->status)
		{
			buf[a] = 0;
			b = len;
		}
	}

	*pp = b;
}


/**
 *x_replace_alias - replaces aliaese
 *@infor: pointer to structure
 *Return: 1 on success or 0
 */
int x_replace_alias(info_t *infor)
{
	int a;
	list_t *node;
	char *pp;

	for (a = 0; a < 10; a++)
	{
		node = node_start_with(infor->alias, infor->argv[0], '=');
		if (!node)
			return (0);
		free(infor->argv[0]);
		pp = _strchr(node->ptr, '=');
		if (!pp)
			return (0);
		pp = _strdup(pp + 1);
		if (!pp)
			return (0);
		infor->argv[0] = pp;
	}
	return (1);
}



/**
 *y_replace_vars - replaces variables
 *@infor: pointer to structure
 *Return: 1 on success or 0
 */
int y_replace_vars(info_t *infor)
{
	int a = 0;
	list_t *node;

	for (a = 0; infor->argv[a]; a++)
	{
		if (infor->argv[a][0] != '$' || !infor->argv[a][1])
			continue;

		if (!_strcmp(infor->argv[a], "$?"))
		{
			replace_string(&(infor->argv[a]),
					_strdup(convert_number(infor->status, 10, 0)));
			continue;
		}
		if (!_strcmp(infor->argv[a], "$$"))
		{
			replace_string(&(infor->argv[a]),
					_strdup(convert_number(getpid(), 10, 0)));
			continue;
		}
		node = node_start_with(infor->env, &infor->argv[a][1], '=');
		if (node)
		{
			replace_string(&(infor->argv[a]),
					_strdup(_strchr(node->ptr, '=') + 1));
			continue;
		}
		replace_string(&infor->argv[a], _strdup(""));

	}
	return (0);
}

