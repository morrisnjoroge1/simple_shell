#include "shell.h"

/**
 *input_buf - Gets the chained input buffer
 *@infor: pointer to structure info_t
 *@buf: double pointer to character buffer
 *@len: integer represents length of string
 *Return: bytes read
 */
ssize_t input_buf(info_t *infor, char **buf, size_t *len)
{
	ssize_t b = 0;
	size_t len_pp = 0;

	if (!*len)
	{
		free(*buf);
		*buf = NULL;
		signal(SIGINT, sigint_handler);
#if USE_GETLINE
		b = getline(buf, &len_pp, stdin);
#else
		b = _getline(infor, buf, &len_pp);
#endif
		if (b > 0)
		{
			if ((*buf)[b - 1] == '\n')
			{
				(*buf)[b - 1] = '\0';
				b--;
			}
			infor->line_count_flag = 1;
			remove_comments(*buf);
			build_history_list(infor, *buf, infor->histcount++);
			{
				*len = b;
				infor->cmd_buf = buf;
			}
		}
	}
	return (b);
}


/**
 *get_input - gets line excluding new line
 *@infor: pointer to structure info_t
 *Return: bytes read
 */
ssize_t get_input(info_t *infor)
{
	static char *buf;
	static size_t a, j, len;
	ssize_t b = 0;
	char **buf_pp = &(infor->arg), *pp;

	_putchar(BUF_FLUSH);
	b = input_buf(infor, &buf, &len);
	if (b == -1) /* End Of File or line */
		return (-1);
	if (len)
	{
		j = a;
		pp = buf + a;

		check_chain(infor, buf, &j, a, len);
		while (j < len)
		{
			if (is_chain(infor, buf, &j))
				break;
			j++;
		}

		a = j + 1;
		if (a >= len)
		{
			a = len = 0;
			infor->cmd_buf_command = CMD_NORM;
		}

		*buf_pp = pp;
		return (_strlen(pp));
	}

	*buf_pp = buf;
	return (b);
}
