#include "shell.h"

char *error_env(char **args);
char *error_1(char **args);
char *error_2_exit(char **args);
char *error_2_cd(char **args);
char *error_2_syntax(char **args);
/**
 * error_env - function that Creates an error message for _env errors.
 * @args: array of arguments passed to command.
 *
 * Return: error string.
 */
char *error_env(char **args)
{
	char *err, *hist_str;
	int length;

	hist_str = itoa(history);
	if (!hist_str)
		return (NULL);

	args--;
	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 45;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": ");
	_strcat(err, args[0]);
	_strcat(err, ": Unable to add/remove from environment\n");

	free(hist_str);
	return (err);
}

/**
 * error_1 - function that Creates an error message for _alias errors.
 * @args: array of arguments to the command.
 *
 * Return: error string.
 */
char *error_1(char **args)
{
	char *err;
	int length;

	length = _strlen(name) + _strlen(args[0]) + 13;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
		return (NULL);

	_strcpy(err, "alias: ");
	_strcat(err, args[0]);
	_strcat(err, " not found\n");

	return (err);
}

/**
 * error_2_exit - function that Creates an error message for _exit errors.
 * @args: array of arguments passed to the command.
 *
 * Return: error string.
 */
char *error_2_exit(char **args)
{
	char *err, *hist_str;
	int length;

	hist_str = itoa(history);
	if (!hist_str)
		return (NULL);

	length = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 27;
	err = malloc(sizeof(char) * (length + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	_strcat(err, ": exit: Illegal number: ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * error_2_cd - function that Creates an error message _cd errors.
 * @args: array of arguments passed to command.
 *
 * Return: error string.
 */
char *error_2_cd(char **args)
{
	char *err, *hist_str;
	int len;

	hist_str = itoa(history);
	if (!hist_str)
		return (NULL);

	if (args[0][0] == '-')
		args[0][2] = '\0';
	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
	err = malloc(sizeof(char) * (len + 1));
	if (!err)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(err, name);
	_strcat(err, ": ");
	_strcat(err, hist_str);
	if (args[0][0] == '-')
		_strcat(err, ": cd: Illegal option ");
	else
		_strcat(err, ": cd: can't cd to ");
	_strcat(err, args[0]);
	_strcat(err, "\n");

	free(hist_str);
	return (err);
}

/**
 * error_2_syntax - Creates an error message for syntax errors.
 * @args: An array of arguments passed to the command.
 *
 * Return: The error string.
 */
char *error_2_syntax(char **args)
{
	char *error, *hist_str;
	int len;

	hist_str = itoa(history);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 33;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": Syntax error: \"");
	_strcat(error, args[0]);
	_strcat(error, "\" unexpected\n");

	free(hist_str);
	return (error);
}


