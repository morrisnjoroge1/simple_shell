#include "shell.h"
#include <string.h>

char *error_126(char **args);
char *error_127(char **args);
int error_create(char **args, int err);

/**
* error_126 - display error message for permission denied failures.
* @args: array pointer to of arguments.
*
* Return: error string.
*/
char *error_126(char **args)
{
char *error, *hist_str;
int len;
hist_str = itoa(history);
if (!hist_str)
return (NULL);

len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 24;
error = malloc(sizeof(char) * (len + 1));
if (!error)
{
free(hist_str);
return (NULL);
}

_strcpy(error, name);
_strcat(error, ": ");
_strcat(error, hist_str);
_strcat(error, ": ");
_strcat(error, args[0]);
_strcat(error, ": Permission denied\n");

free(hist_str);
return (error);
}

/**
* error_127 - display error message for command not found
* @args: array of arguments
*
* Return: error message
*/
char *error_127(char **args)
{
int len;
char *error, *hist_str;

hist_str = itoa(history);
	if (!hist_str)
		return (NULL);

	len = _strlen(name) + _strlen(hist_str) + _strlen(args[0]) + 16;
	error = malloc(sizeof(char) * (len + 1));
	if (!error)
	{
		free(hist_str);
		return (NULL);
	}

	_strcpy(error, name);
	_strcat(error, ": ");
	_strcat(error, hist_str);
	_strcat(error, ": ");
	_strcat(error, args[0]);
	_strcat(error, ": not found\n");

	free(hist_str);
	return (error);
}

/**
* error_create - Writes a  error message to stderr.
* @args: array of arguments.
* @err: error value.
*
* Return: error value.
*/
int error_create(char **args, int err)
{
char *error;

switch (err)
{
case -1:
error = error_env(args);
break;
case 1:
error = error_1(args);
break;
case 2:
if (*(args[0]) == 'e')
error = error_2_exit(++args);
else if (args[0][0] == ';' || args[0][0] == '&' || args[0][0] == '|')
error = error_2_syntax(args);
else
error = error_2_cd(args);
break;
case 126:
error = error_126(args);
break;
case 127:
error = error_127(args);
break;
}
write(STDERR_FILENO, error, _strlen(error));

if (error)
free(error);
return (err);

}



