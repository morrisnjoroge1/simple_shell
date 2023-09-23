#include "shell.h"

/**
 *get_history_file - gets history file thst store history of linked lists
 *@infor: pointer to structure parameters
 *Return: string containing history file
 */
char *get_history_file(info_t *infor)
{
	char *buf, *dir;

	dir = _getenv(infor, "HOME=");
	if (!dir)
		return (NULL);
	buf = malloc(sizeof(char) * (_strlen(dir) + _strlen(HIST_FILE) + 2));
	if (!buf)
		return (NULL);
	buf[0] = 0;
	_strcpy(buf, dir);
	_strcat(buf, "/");
	_strcat(buf, HIST_FILE);
	return (buf);
}


/**
 *hist_read - read the history of linked list
 *@infor: poiter to sturcture parametrs
 *Return: history count or 0
 */
int hist_read(info_t *infor)
{
	int a, last = 0, line_count = 0;
	ssize_t pd, rlen, fsize = 0;
	struct stat st;
	char *buf = NULL, *filename = get_history_file(infor);

	if (!filename)
		return (0);

	pd = open(filename, O_RDONLY);
	free(filename);
	if (pd == -1)
		return (0);
	if (!fstat(pd, &st))
		fsize = st.st_size;
	if (fsize < 2)
		return (0);
	buf = malloc(sizeof(char) * (fsize + 1));
	if (!buf)
		return (0);
	rlen = read(pd, buf, fsize);
	buf[fsize] = 0;
	if (rlen <= 0)
		return (free(buf), 0);
	close(pd);
	for (a = 0; a < fsize; a++)
		if (buf[a] == '\n')
		{
			buf[a] = 0;
			build_history_list(infor, buf + last, line_count++);
			last = a + 1;
		}
	if (last != a)
		build_history_list(infor, buf + last, line_count++);
	free(buf);
	infor->histcount = line_count;
	while (infor->histcount-- >= HIST_MAX)
		delete_node_at_index(&(infor->history), 0);
	hist_renumber(infor);
	return (infor->histcount);
}


/**
 *hist_write - creates, writes and appends the history of linked lists
 *@infor: pointer to structure
 *Return: 1 on success or -1 otherwise
 */
int hist_write(info_t *infor)
{
	ssize_t pd;
	char *filename = get_history_file(infor);
	list_t *node = NULL;

	if (!filename)
		return (-1);

	pd = open(filename, O_CREAT | O_TRUNC | O_RDWR, 0644);
	free(filename);
	if (pd == -1)
		return (-1);
	for (node = infor->history; node; node = node->next)
	{
		_putsfd(node->ptr, pd);
		_putfd('\n', pd);
	}
	_putfd(BUF_FLUSH, pd);
	close(pd);
	return (1);
}


/**
 *build_history_list - Keeps record of the history linked list
 *@infor: pointer to structure parameters
 *@buf: pointer to character buffer
 *@line_count: history count line
 *Return: 0
 */
int build_history_list(info_t *infor, char *buf, int line_count)
{
	list_t *node = NULL;

	if (infor->history)
		node = infor->history;
	add_node_end(&node, buf, line_count);

	if (!infor->history)
		infor->history = node;
	return (0);
}


/**
 *hist_renumber - renumbers the history in linked lists
 *@infor: pointer to structure parameters
 *Return: new history count
 */
int hist_renumber(info_t *infor)
{
	list_t *node = infor->history;
	int a = 0;

	while (node)
	{
		node->num = a++;
		node = node->next;
	}
	return (infor->histcount = a);
}
