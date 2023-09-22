#include "shell.h"

/**
 *is_cmd - checks if file is an executable command
 *@infor: pointer to structure parameters
 *@path: file path
 *Return: 1 on success or 0 on error
 */
int is_cmd(info_t *infor, char *path)
{
	struct stat st;

	(void)infor;
	if (!path || stat(path, &st))
		return (0);

	if (st.st_mode & S_IFREG)
	{
		return (1);
	}
	return (0);
}


/**
 *find_path - finds the path of command i PATH
 *@infor: pointer to structure parameters in info_t
 *@pathstar: PATH string
 *@cmd: cmd used to find
 *Return: full PATH or null
 */
char *find_path(info_t *infor, char *pathstar, char *cmd)
{
	int a = 0, curr_posi = 0;
	char *path;

	if (!pathstar)
		return (NULL);
	if ((_strlen(cmd) > 2) && start_with(cmd, "./"))
	{
		if (is_cmd(infor, cmd))
			return (cmd);
	}
	while (1)
	{
		if (!pathstar[a] || pathstar[a] == ':')
		{
			path = _dupchars(pathstar, curr_posi, a);
			if (!*path)
				_strcat(path, cmd);
			else
			{
				_strcat(path, "/");
				_strcat(path, cmd);
			}
			if (is_cmd(infor, path))
				return (path);
			if (!pathstar[a])
				break;
			curr_posi = a;
		}
		a++;
	}
	return (NULL);
}


/**
 *_dupchars - duplicates characters
 *@pathstar: PATH string
 *@start: index
 *@stop: index
 *Return: newbuffer pointer
 */
char *_dupchars(char *pathstar, int start, int stop)
{
	static char buf[1024];
	int a = 0, k = 0;

	for (k = 0, a = start; a < stop; a++)
		if (pathstar[a] != ':')
			buf[k++] = pathstar[a];
	buf[k] = 0;
	return (buf);
}
