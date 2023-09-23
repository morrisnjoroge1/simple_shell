#include "shell.h"

/*we handle the exit command*/
/*handles change of directory commnad*/
/*handles help incase i=of errors occurred*/

/**
 *my_exit - handles the exit command in the shell
 *@infor: pointer to structure info_t
 *Return: the exit status of the program
 */
int my_exit(info_t *infor)
{
	int exitchecks;

	if (infor->argv[1])
	{
		exitchecks = _erritoa(infor->argv[1]);
		if (exitchecks == -1)
		{
			infor->status = 2;
			prints_error(infor, "Illegal number: ");
			_eputs(infor->argv[1]);
			_eputchar('\n');
			return (1);
		}
		infor->err_num = _erritoa(infor->argv[1]);
		return (-2);
	}
	infor->err_num = -1;
	return (-2);
}


/**
 *my_cd - Handles the command that helps in changing directories
 *@infor: pointer to stucture info_t
 *Return: 0 upon success
 */
int my_cd(info_t *infor)
{
	char *s, *dir, buffer[1024];
	int chdir_rec;

	s = getcwd(buffer, 1024);
	if (!s)
		_puts("TODO: >>getcwd failure emsg here<<\n");
	if (!infor->argv[1])
	{
		dir = _getenv(infor, "HOME=");
		if (!dir)
			chdir_rec =
				chdir((dir = _getenv(infor, "PWD=")) ? dir : "/");
		else
			chdir_rec = chdir(dir);
	}
	else if (_strcmp(infor->argv[1], "-") == 0)
	{
		if (!_getenv(infor, "OLDPWD="))
		{
			_puts(s);
			_putchar('\n');
			return (1);
		}
		_puts(_getenv(infor, "OLDPWD=")), _putchar('\n');
		chdir_rec =
			chdir((dir = _getenv(infor, "OLDPWD=")) ? dir : "/");
	}
	else
		chdir_rec = chdir(infor->argv[1]);
	if (chdir_rec == -1)
	{
		prints_error(infor, "can't cd to ");
		_eputs(infor->argv[1]), _eputchar('\n');
	}
	else
	{
		_setenv(infor, "OLDPWD", _getenv(infor, "PWD="));
		_setenv(infor, "PWD", getcwd(buffer, 1024));
	}
	return (0);
}

/**
 *my_help - Function that help incase of errors encountered in
 *changing the directory
 *@infor: pointer to structure
 *Return: 0 always
 */
int my_help(info_t *infor)
{
	char **arg_arr;

	arg_arr = infor->argv;
	_puts("help call works. Function not yet implemented \n");
	if (0)
		_puts(*arg_arr);
	return (0);
}
