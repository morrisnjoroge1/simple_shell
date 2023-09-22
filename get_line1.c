#include "shell.h"

/**
 *_getline - Function that gets the next line of user input in stdinput
 *@infor: pointer to structure info_t
 *@str: pointer to character string
 *@length: pointer to character that stores length
 *Return: s
 */
int _getline(info_t *infor, char **str, size_t *length)
{
	static char buf[READ_BUF_SIZE];
	static size_t a, len;
	size_t b;
	ssize_t r = 0, s = 0;
	char *pp = NULL, *new_pp = NULL, *c;

	pp = *str;
	if (pp && length)
		s = *length;
	if (a == len)
		a = len = 0;
	r = read_buf(infor, buf, &len);
	if (r == -1 || (r == 0 && len == 0))
		return (-1);
	c = _strchr(buf + i, '\n');
	b = c ? 1 + (unsigned int)(c - buf) : len;
	new_pp = _realloc(pp, s, s ? s + b : b + 1);
	if (!new_pp)
		return (pp ? free(pp), -1 : -1);

	if (s)
		_strncat(new_pp, buf + a, b - a);
	else
		_strncpy(new_pp, buf + a, b - a + 1);

	s += b - a;
	a = b;
	pp = new_pp;

	if (length)
		*length = s;
	*str = pp;
	return (s);
}


/**
 *sigint_handler - handles the signal CTRL+C
 *@sig_num: integer
 *Return: void
 */
void sigint_handler(__attribute__((unused))int sig_num)
{
	_puts("\n");
	_puts("$ ");
	_putchar(BUF_FLUSH);
}
