#include "shell.h"

/**
 *hsh - the shell loop
 *@infor: pointer to structure info_t
 *@av: argument vector or array
 *Return: 0 on success or 1 upon error
 */
int hsh(info_t *infor, char **av)
{
	ssize_t b = 0;
	int builtin_rec = 0;

	while (b != -1 && builtin_rec != -2)
	{
		clear_info(infor);
		if (x_interactive(infor))
			_puts("$ ");
		_eputchar(BUF_FLUSH);
		b = get_input(infor);
		if (b != -1)
		{
			set_info(infor, av);
			builtin_rec = find_builtin(infor);
			if (builtin_ret == -1)
				find_cmd(infor);
		}
		else if (x_interactive(infor))
			_putchar('\n');
		free_info(infor, 0);
	}
	hist_writey(infor);
	free_info(infor, 1);
	if (!x_interactive(infor) && infor->status)
		exit(infor->status);
	if (builtin_rec == -2)
	{
		if (infor->err_num == -1)
			exit(infor->status);
		exit(infor->err_num);
	}
	return (builtin_rec);
}


/**
 *find_builtin - Function that finds builtin commands
 *@infor: pointer to structure info_t
 *Return: 0 on success or -1 otherwise
 */
int find_builtin(info_t *infor)
{
	int a, built_in_rec = -1;
	builtin_t built[] = {
		{"exit", my_exit},
		{"env", my_env},
		{"help", my_help},
		{"history", my_history},
		{"setenv", _my_setenv},
		{"unsetenv", _my_unsetenv},
		{"cd", my_cd},
		{"alias", my_alias},
		{NULL, NULL}
	};

	for (a = 0; built[a].command; a++)
		if (_strcmp(infor->argv[0], built[a].command) == 0)
		{
			infor->_line_count++;
			built_in_rec = built[a].func(infor);
			break;
		}
	return (built_in_rec);
}


/**
 *find_cmd - finds command in PATH
 *@infor: pointer to structure info_t
 *Return: void
 */
void find_cmd(info_t *infor)
{
	char *path = NULL;
	int a, k;

	infor->path = infor->argv[0];
	if (infor->line_count_flag == 1)
	{
		infor->_line_count++;
		infor->line_count_flag = 0;
	}
	for (a = 0, k = 0; infor->arg[a]; a++)
		if (!is_delim(infor->arg[i], " \t\n"))
			k++;
	if (!k)
		return;

	path = find_path(infor, _getenv(infor, "PATH="), infor->argv[0]);
	if (path)
	{
		infor->path = path;
		fork_cmd(infor);
	}
	else
	{
		if ((x_interactive(infor) || _getenv(infor, "PATH=")
					|| infor->argv[0][0] == '/') && is_cmd(infor, infor->argv[0]))
			fork_cmd(infor);
		else if (*(infor->arg) != '\n')
		{
			infor->status = 127;
			prints_error(infor, "not found\n");
		}
	}
}


/**
 *fork_cmd - forks executable command thread to run
 *@infor: pointer to structure
 *Return: void
 */
void fork_cmd(info_t *infor)
{
	pid_t child_pid;

	child_pid = fork();
	if (child_pid == -1)
	{
		perror("Error:");
		return;
	}
	if (child_pid == 0)
	{
		if (execve(infor->path, infor->argv, get_environ(infor)) == -1)
		{
			free_info(infor, 1);
			if (errno == EACCES)
				exit(126);
			exit(1);
		}
	}
	else
	{
		wait(&(infor->status));
		if (WIFEXITED(infor->status))
		{
			infor->status = WEXITSTATUS(infor->status);
			if (infor->status == 126)
				prints_error(infor, "Permission denied\n");
		}
	}
}
