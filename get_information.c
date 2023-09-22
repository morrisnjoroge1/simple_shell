#include "shell.h"

/**
 *clear_info - clears information
 *@infor: pointer to structure infor_t
 *Return: void
 */
void clear_info(info_t *infor)
{
	infor->arg = NULL;
	infor->argv = NULL;
	infor->path = NULL;
	infor->argc = 0;
}


/**
 *set_info - sets information
 *@infor: pointer to structure
 *@av: character pointer to arguments
 *Return: void
 */
void set_info(info_t *infor, char **av)
{
	int a = 0;

	infor->fname = av[0];
	if (infor->arg)
	{
		infor->argv = strtox(infor->arg, " \t");
		if (!infor->argv)
		{
			infor->argv = malloc(sizeof(char *) * 2);
			if (infor->argv)
			{
				infor->argv[0] = _strdup(infor->arg);
				infor->argv[1] = NULL;
			}
		}
		for (a = 0; infor->argv && infor->argv[a]; a++)
			;
		infor->argc = a;

		x_replace_alias(infor);
		y_replace_vars(infor);
	}
}


/**
 *free_info - Fress information
 *@infor: pointer to structure parameters
 *@all: integer fields to free
 *Return: void
 */
void free_info(info_t *infor, int all)
{
	f_free(infor->argv);
	infor->argv = NULL;
	infor->path = NULL;
	if (all)
	{
		if (!infor->cmd_buf)
			free(infor->arg);
		if (infor->env)
			free_list(&(infor->env));
		if (infor->history)
			free_list(&(infor->history));
		if (infor->alias)
			free_list(&(infor->alias));
		f_free(infor->environ);
			infor->environ = NULL;
		b_free((void **)infor->cmd_buf);
		if (infor->readfd > 2)
			close(infor->readfd);
		_putchar(BUF_FLUSH);
	}
}
